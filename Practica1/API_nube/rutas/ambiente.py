from fastapi import APIRouter
from esquema.ambiente import Ambiente

ruta_ambiente = APIRouter()

database = []

@ruta_ambiente.post("/register", response_model=Ambiente)
def prueba(ambiente: Ambiente):
    try:
        # BASE DE DATOS LOCAL
        database.append(ambiente.__dict__)
        return ambiente
    
    except Exception as e:
        return e