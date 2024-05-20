FROM linuxserver/ffmpeg:latest

WORKDIR /app

RUN apt-get update && apt-get upgrade
RUN apt-get install -y build-essential cmake

COPY . .

RUN cmake -B build && make -C build

ENTRYPOINT ["/app/build/camrecv"]
