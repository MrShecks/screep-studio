# Screeps API
This file contains my notes on the Screeps game API

The information has been gathered by reading through the Screeps private server source code, various Screeps related open source tools and libraries and
in some cases, by observing the communication between the Screeps Steam client and server using WireShark.

The Screeps game API consists of two APIs, a web based REST API and a Web Socket API. In general the REST API is used to query static information
about the game entities (e.g Server information, world structure, room terrain) and the Web Socket API provides a mechanism to subscribe to
event streams to receive live notifications of changes applied to game entities.

## Sources

- Official Screeps Private Server [source](https://github.com/screeps/screeps)
- Node.js [Screeps-API](https://github.com/screepers/node-screeps-api) library and [documents](https://github.com/screepers/node-screeps-api/blob/master/docs/Websocket_endpoints.md)
- Python-Screeps endpoint [document](https://github.com/screepers/python-screeps/blob/master/docs/Endpoints.md)


## REST API
---
### Base endpoint
The base end point for REST calls is formatted as follows:-

    <http|https>://<hosts>:<port>/api/

E.g

    https://screeps.com:443/api/
    https://192.168.1.50:21025/api/

- The public test realm on screeps.com uses the endpoint "http://screeps.com:443/ptr/api/"
- The default REST API port for private servers is 21025.
- Unless otherwise noted, all request and response bodies are formatted as JSON.

Throughout the remainder of this document the REST end point will be referred to as \<base-endpoint\>

### Server Version
---
Request information about the server.

#### HTTP GET

    <base-endpoint>/version

#### Response Body:

  Example 1
  Basic information as currently returned from the live server.

```json
{
  "ok": 1,
  "package": 145,
  "protocol": 13,
  "serverData": {
    "historyChunkSize": 100,
    "shards": [
      "shard0",
      "shard1",
      "shard2",
      "shard3"
    ]
  }
}
```

  Example 2    
  Server response from a server providing additional custom information in the "serverData" object.

```json
{
    "ok": 1,
    "protocol": 13,
    "useNativeAuth": false,
    "users": 2,
    "serverData": {
        "welcomeText": "<h4>Welcome to your own Screeps private server!</h4>This text can be changed by adding a mod to your server, see <code>mods.json</code> file in your server folder.",
        "customObjectTypes": {},
        "historyChunkSize": 20,
        "socketUpdateThrottle": 1000,
        "renderer": {
            "resources": {},
            "metadata": {}
        }
    },
    "packageVersion": "3.1.7"
}
```

### Authentication (Screeps)
---
#### Steam Ticket
Authenticate user via Steam authentication ticket

Screeps API authentication tokens/tickets are associated with your Steam signon credentials and can be created [here](https://screeps.com/a/#!/account/auth-tokens)

##### HTTP POST

    <rest-endpoint>/auth/steam-ticket

##### Request Body

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| ticket | String | Authentication ticket |
| useNativeAuth | Boolean | Enable native login<BR>The value of this parameter should match the value returned in the /version response  |


Example

```json
{
  "ticket": "df174549-8086-2b9f-94e4-74dd0c4fd555",
  "useNativeAuth": false
}
```    

##### Response Body

```json
{
  "ok": 1,
  "token": "5581204567890abcdef4b56437e687bbe932ed89"
}
```    

#### User Sign In
Authenticate user by signing in with email/username and password

##### HTTP POST

    <rest-endpoint>/auth/signin

##### Request Body

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| email | String | Username/Email address |
| password | String | User password |


Example

```json
{
  "email": "screepy@protonmail.com",
  "password": "mysecretpassword",
}
```

##### Response Body

#### User Information
Request information about the currently authenticated user

##### HTTP GET

    <base-endpoint>/auth/me

##### Response Body

```json
{
    "_id":"f99b7db35b10edd",
    "badge":{
        "color1":"#00770e",
        "color2":"#ffffff",
        "color3":"#ffff00",
        "flip":false,
        "param":0,
        "type":3
    },
    "blocked":false,
    "cpu":100,
    "gcl":0,
    "money":0,
    "ok":1,
    "password":true,
    "steam":{
        "id":"55512345678900000"
    },
    "username":"Fred"
}
```    

### Authentication (screepsmod-auth)
---
#### AuthMod Information
This call can be used to determine if the [screeps-authmod](https://github.com/ScreepsMods/screepsmod-auth) modification is installed. If successful it returns version and configuration information about the mod.

#### HTTP GET

    <base-endpoint>/authmod

#### Response Body

```json
{
  "ok":1,
  "name":"screepsmod-auth",
  "version":"2.4.7",
  "allowRegistration":true,
  "steam":true,
  "github":false
}    
```


### User Registration
---
#### Register New User
Register a new user on the server

#### HTTP POST

    <base-endpoint>/register/submit

#### Request Body

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| username | String | Username to register |
| password | String | Account password |
| email | String | (Optional) Email address |

Example

```json
{
    "username": "screepymacscreepface",
    "password": "mysecretpassword",
    "email": "screepy@protonmail.com"
}
```

#### Response Body

#### Set Username
Set username

#### HTTP POST

#### Check Username
Check if a given username exists on the server already

#### HTTP GET

    <base-endpoint>/register/check-username?username=screepymacscreepface

#### Response Body
Since this API is used during registration it return an error if the username exists and no error if the username does not exist (e.g it's free to use)

Example 1: Username exists

```json
{
  "error":"exists"
}
```

Example 2: Username does not exist

```json
{
  "ok":1
}
```

#### Check Email
Check if a given email address exists on the server

#### HTTP GET

    <base-endpoint>/register/check-email?email=screepy@protonmail.com

#### Response Body
Since this API is used during registration it returns an error if the email address exists and no error if the email address does not exist (e.g it's free to use)

Example 1: Email address exists

```json
{
  "error":"exists"
}
```

Example 2: Email address does not exist

```json
{
  "ok":1
}
```

### User
---
#### Find User
Retrieve information about an existing user by username or ID

#### HTTP GET
Find user by username

    <base-endpoint>/user/find?username=screepymacscreepface

Find user by ID

    <base-endpoint>/user/find?id=55c91dc66e36d62a6167e1b5

#### Response Body

```json
{
  "ok":1,
  "user":{
    "_id":"68d45702409f1ea41ef407d9d",
    "steam":{
      "id":"88927198255293883"
      },
      "username":"screepymacscreepface",
      "badge":{
        "type":7,
        "color1":"#287710",
        "color2":"#ffff2f",
        "color3":"#d86530",
        "param":100,
        "flip":false
      },
      "gcl":1254059
    }
}
```

#### User Console
Submit a command to the user console

#### HTTP POST

    <base-endpoint>/user/console?expression=Hello&shard=shard0

#### Response Body

### Game
---


## Web Socket API
TODO: Gather up information about the Screeps Web Socket API
