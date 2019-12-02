# Screeps API
This file contains my notes on the Screeps game API

The information has been gathered by reading through the Screeps private server source code, various Screeps related open source tools and libraries and
in some cases, by observing the communication between the Screeps Steam client and server using WireShark.

The Screeps game API consists of two APIs, a web based REST API and a Web Socket API. In general the REST API is used to query static information
about the game entities (e.g Server information, world structure, room terrain) and the Web Socket API provides a mechanism to subscribe to
event streams to receive live notifications of changes applied to game entities.

## Sources

- Official Screeps Private Server [source](https://github.com/screeps/screeps)
- Node.js [Screeps-API](https://github.com/screepers/node-screeps-api) library


## REST API

### Base endpoint
The base end point for REST calls is formatted as follows:-

    <http|https>://<hosts>:<port>/api/

E.g

    https://screeps.com:443/api/
    https://192.168.1.50:21025/api/

The default port for private servers is 21025.

Throughout the remainder of this document the REST end point will be referred to as \<base-endpoint\>

#### Server Version
Request information about the server.

##### HTTP GET

    <base-endpoint>/version

##### Response Body:

  Example 1
  Basic information as currently returned from the live server.

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

  Example 2    
  Server response from a server providing additional custom information in the "serverData" object.

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

### Authentication

#### Steam Ticket
Authenticate user via Steam authentication ticket

Screeps API authentication tokens/tickets are associated with your Steam signon credentials and can be created [here](https://screeps.com/a/#!/account/auth-tokens)

##### HTTP POST

    <rest-endpoint>/auth/steam-ticket

##### Request Body

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| ticket | String | Authentication ticket |
| useNativeAuth | Boolean | Enable native login (FIXME: Get more information on this flag) |

Example

    {
      "ticket": "df174549-8086-2b9f-94e4-74dd0c4fd555",
      "useNativeAuth": false
    }

##### Response Body

    {
      "ok": 1,
      "token": "5581204567890abcdef4b56437e687bbe932ed89"
    }

#### User Sign In
Authenticate user by signing in with username and password

##### HTTP POST

    <rest-endpoint>/auth/signin

##### Request Body

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| username | String | Login user name |
| password | String | User password |
| email | String | Email address (Optional) |

Example

    {
      "username": "screepymacscreepface",
      "password": "mysecretpassword"
      "email": "screepy@protonmail.com"
    }

##### Response Body

#### User Information
Request information about the currently authenticated user

##### HTTP GET

    <base-endpoint>/auth/me

##### Response Body

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

## Web Socket API
TODO: Gather up information about the Screeps Web Socket API
