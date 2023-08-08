from typing import List
from fastapi import APIRouter
from redis_client.crud import (
    delete_all_hash,
    delete_hash,
    get_all_hash,
    get_hash,
    save_hash,
    update_hash,
)
from schemas.sensors import Sensor

routes_sensor = APIRouter()


# Create a new sensor
@routes_sensor.post("/create", response_model=List[Sensor])
def create(sensors: List[Sensor]):
    try:
        for sensor in sensors:
            # REDIS
            save_hash(key=sensor.model_dump()["id"], data=sensor.model_dump())
            pass
        return sensors

    except Exception as e:
        return {"error": str(e)}


# Get a sensor by id
@routes_sensor.get("/read/{id}")
def get(id: str):
    try:
        # REDIS
        data = get_hash(key=id)
        if len(data) > 0:
            return data
        else:
            return {"message": "sensor not found"}

    except Exception as e:
        return e


# Get all sensors
@routes_sensor.get("/read")
def get_all():
    try:
        # REDIS
        return get_all_hash()

    except Exception as e:
        return e


# Update a sensor by id
@routes_sensor.put("/update/{id}", response_model=Sensor)
def update(id: str, updated_sensor: Sensor):
    try:
        data = get_hash(key=id)

        if len(data) == 0:
            return {"message": "sensor not found"}

        # Read only the updated values
        updated_data = updated_sensor.model_dump(exclude_unset=True)

        # Update the values
        data.update(**updated_data)

        # REDIS
        update_hash(key=id, data=data)

        return data

    except Exception as e:
        print("An exception occurred")
        return e


# Delete a sensor by id
@routes_sensor.delete("/delete/{id}")
def delete(id: str):
    try:
        keys = Sensor.__fields__.keys()
        delete_hash(key=id, keys=keys)

        return {"message": "Sensor deleted successfully"}

    except Exception as e:
        return {"error": str(e)}


# Delete all sensors
@routes_sensor.delete("/deleteall")
def delete_all():
    try:
        # REDIS
        delete_all_hash()
        
        return {"message": "all sensors deleted successfully"}
    
    except Exception as e:
        return {"error": str(e)}
