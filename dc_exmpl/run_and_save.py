import subprocess
import psycopg2
import time

def run_command(command):
    result = subprocess.run(
        command,
        shell=True,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT
    )

    return result.returncode, result.stdout

def connect_to_db():
    for i in range(20):
        try:
            return psycopg2.connect(
                host="db",
                database="syrk_db",
                user="syrk_user",
                password="syrk_password"
            )
        except psycopg2.OperationalError as e:
            print(f"БД ещё не готова, попытка {i + 1}/20")
            print(e)
            time.sleep(2)

    raise Exception("Не удалось подключиться к БД")

conn = connect_to_db()

cur = conn.cursor()

print("=== Сборка проекта ===")

code, output = run_command(
    "cmake -S . -B build && cmake --build build"
)

print(output)

build_status = "passed" if code == 0 else "failed"

cur.execute(
    "INSERT INTO test_results (test_name, status, output) VALUES (%s, %s, %s)",
    ("build", build_status, output)
)

conn.commit()

if code != 0:
    print("Ошибка сборки")
    exit(1)

print("=== UNIT TEST ===")

code, output = run_command("./build/test_syrk")

print(output)

status = "passed" if code == 0 else "failed"

cur.execute(
    "INSERT INTO test_results (test_name, status, output) VALUES (%s, %s, %s)",
    ("test_syrk", status, output)
)

print("=== CBLAS INTERFACE TESTS ===")

code, output = run_command("./build/all_cblas_tests")

print(output)

status = "passed" if code == 0 else "failed"

cur.execute(
    "INSERT INTO test_results (test_name, status, output) VALUES (%s, %s, %s)",
    ("all_cblas_tests", status, output)
)

print("=== DGEMM TEST ===")

code, output = run_command("./build/test_dgemm")

print(output)

status = "passed" if code == 0 else "failed"

cur.execute(
    "INSERT INTO test_results (test_name, status, output) VALUES (%s, %s, %s)",
    ("test_dgemm", status, output)
)

print("=== BENCHMARK ===")

code, output = run_command("./build/bench_syrk")

print(output)

cur.execute(
    "INSERT INTO benchmark_results (benchmark_name, output) VALUES (%s, %s)",
    ("bench_syrk", output)
)

conn.commit()

cur.close()
conn.close()

print("=== Все результаты записаны в БД ===")
