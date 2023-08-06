from redis import Redis
from redis.exceptions import ConnectionError
from os import getenv


try:
    redis_client = Redis(
        host='us1-lasting-loon-38131.upstash.io',
        port=38131,
        password='1875241040494314b87e11bb6933ea3a'
    )

    print("Connected to Redis")
except ConnectionError as e:
    print("Connection to Redis failed")
    print(e)