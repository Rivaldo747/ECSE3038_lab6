from pickle import APPEND
from fastapi import FastAPI,Request
from fastapi import FastAPI, HTTPException
from bson import ObjectId
from fastapi.middleware.cors import CORSMiddleware
import motor.motor_asyncio
import pydantic
import datetime

app= FastAPI()

origins=[
   
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

client=motor.motor_asyncio.AsyncIOMotorClient("mongodb+srv://Rivbot:ZImDfWoUlYlRUjKh@cluster0.oinoodt.mongodb.net/?retryWrites=true&w=majority")
pydantic.json.ENCODERS_BY_TYPE[ObjectId]=str
@app.get("/api/state")
async def get_state():
  state = await db["data"].info({"": "mon"})

  if state == None:
    return {"fan": False, "light": False}
  return state



@app.put("/api/state")
async def capture(request: Request): 
  
  update = await request.json()

  sunset = requests.get('https://ecse-sunset-api.onrender.com/api/sunset').json()
  response = requests.get(url)
    data = response.json()
    sunset_time_str = data['results']['sunset']
    sunset_time = datetime.strptime(sunset_time_str, '%I:%M:%S %p')
    return sunset_time

  update["light"] = (datetime1<datetime2)
  update["fan"] = (float(update["temperature"]) >= 28.0) 
 find = await db["data"].find_one({"poke": "mon"})
   find = await db["data"].find_one({"poke": "mon"})
  
  if find:
    await db["data"].update_one(({"poke": "mon"}), {"$set": update})
    find = await db["data"].find_one({"poke": "mon"})
    return find,204
  else:
    await db["data"].insert_one({**update, "poke": "mon"})
    find = await db["data"].find_one({"poke": "mon"})
    return find,204
