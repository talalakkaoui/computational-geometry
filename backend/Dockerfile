# Stage 1: build the C++ server
FROM ubuntu:22.04 AS builder

RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    make \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN cmake -S . -B build \
    && cmake --build build --config Release

# Stage 2: minimal runtime image
FROM ubuntu:22.04 AS runtime

COPY --from=builder /app/build/server/server /usr/local/bin/geometry-server

ARG PORT=8080
ENV PORT=${PORT}
EXPOSE ${PORT}

CMD ["geometry-server"]
