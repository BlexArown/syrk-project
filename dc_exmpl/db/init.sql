CREATE TABLE IF NOT EXISTS test_results (
    id SERIAL PRIMARY KEY,
    test_name TEXT NOT NULL,
    status TEXT NOT NULL,
    output TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS benchmark_results (
    id SERIAL PRIMARY KEY,
    benchmark_name TEXT NOT NULL,
    output TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
