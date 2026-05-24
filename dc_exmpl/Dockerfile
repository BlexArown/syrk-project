FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libopenblas-dev \
    python3 \
    python3-pip \
    postgresql-client \
    && rm -rf /var/lib/apt/lists/*

RUN pip3 install psycopg2-binary

WORKDIR /app

COPY . /app

CMD ["python3", "run_and_save.py"]
