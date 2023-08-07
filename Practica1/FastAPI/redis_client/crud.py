from .connection import redis_client
from redis.exceptions import ResponseError


def save_hash(key: str, data: dict):
    try:
        redis_client.hmset(key, data)
        redis_client.lpush("sensors", key)
    except ResponseError as e:
        print("An exception occurred")
        print(e)


def get_hash(key: str):
    try:
        data = redis_client.hgetall(key)
        return data
    except ResponseError as e:
        print("An exception occurred")
        print(e)


def get_all_hash():
    try:
        all_keys = redis_client.lrange("sensors", 0, -1)
        sensors = []

        for current_key in all_keys:
            sensor = redis_client.hgetall(current_key)
            sensors.append(sensor)

        return sensors
    except ResponseError as e:
        print("An exception occurred")
        print(e)

def update_hash(key: str, data: dict):
    try:
        redis_client.hmset(key, data)
    except ResponseError as e:
        print("An exception occurred")
        print(e)

def delete_hash(key: str, keys: list):
    try:
        redis_client.hdel(key, *keys)
        redis_client.lrem("sensors", 1, key)
    except ResponseError as e:
        print("An exception occurred")
        print(e)


def delete_all_hash():
    try:
        all_keys = redis_client.lrange("sensors", 0, -1)

        for current_key in all_keys:
            redis_client.hdel(current_key, *redis_client.hkeys(current_key))
            redis_client.lrem("sensors", 1, current_key)
    except ResponseError as e:
        print("An exception occurred")
        print(e)