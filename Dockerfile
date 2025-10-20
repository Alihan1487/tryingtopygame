FROM dorowu/ubuntu-desktop-lxde-vnc

# Обновляем репозитории и устанавливаем SFML
RUN rm -f /etc/apt/sources.list.d/google-chrome.list
RUN apt-get update --allow-unauthenticated && apt-get install -y \
    g++ \
    cmake \
    libsfml-dev \
    apt-transport-https \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN cmake -DSFML_STATIC_LIBS=TRUE . && make

# CMD нужно писать в JSON формате
CMD ["./app"]
