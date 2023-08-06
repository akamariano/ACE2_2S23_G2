from fastapi import APIRouter
from redis_client.crud import save_hash
from schemas.sensors import Sensor

routes_sensor = APIRouter()
fake_db = []

@routes_sensor.post("/create", response_model=Sensor)
def create(sensor: Sensor):
    try:
        fake_db.append(sensor.model_dump())
        
        # REDIS
        save_hash(key = sensor.model_dump()["id"], data = sensor.model_dump())

        return sensor
    except Exception as e:
        return e

@routes_sensor.get("/read/{id}")
def get(id: str):
    try:
        # for sensor in fake_db:
        #     if sensor["id"] == id:
        #         return sensor
        # return {"message": "sensor not found"}
        return list(filter(lambda field: field["id"] == id, fake_db))[0]
    except Exception as e:
        return e
    
@routes_sensor.delete("/delete/{id}")
def delete(id: str):
    try:
        global fake_db
        fake_db = [field for field in fake_db if field.get("id") != id]
        return {"message": "Sensor deleted successfully"}
    except Exception as e:
        return {"error": str(e)}