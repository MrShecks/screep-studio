Screeps WebSocket Protocol
--------------------------

Endpoint:

ws://[host]:[port]/socket/websocket
wss://[host]:[port]/socket/websocket

Note: The Web browser client opens the following WebSocket on the live server
wss://screeps.com/socket/786/3bhlipnu/websocket

There's also a REST call to https://screeps.com/socket/info but it result in a 502 Bad Gateway response

---------------------------------------------------------------
Regular Expressions
---------------------------------------------------------------

Channel subscriptions and channel events return a JSON array with 2 elements, as follows:-

[ "<identifier>", "{ <JSON object> }"]

To quickly check if the message is a channel subscription or channel event rather than a regular command reply we can use the following
regular expression:-

^\[(.+)\]$

Which simply checks if the message starts with "[" and ends with "]" (a JSON array)

The first element will always be an identifier that can be used to determine which channel or channel element the message relates too.

Pattern use to match and extract the ID components of the first element of the JSON array returned
for Websocket subscription and event Messages:

^(.+):(.+?)(?:\/(.+))?$

Example:

"room:W0N0""

---------------------------------------------------------------
Connection
---------------------------------------------------------------

On successful connection the server sends the following information to the client

time[space][time]<CR>
protocol[space][protocol]<CR>

Where:
	[time] numeric, representing the number of milliseconds since midnight January 1, 1970
	[protocol] numeric protocol version

Example:

time 1543956203659
protocol 13

Authentication
--------------------------

auth[space][token]

Return:

auth[space]ok[space][token]
auth[space]failed

Example:

auth 9ec5155f0c34edaa655b4df4b3e3abd58f9b0355

Note: The auth token returned is not the same as the token sent, not sure where this
new token is used yet.

---------------------------------------------------------------
Channel Subscriptions
---------------------------------------------------------------


| Command | Parameters | Description |
| ------- | ---------- | ------------|
| subscribe | channel | Add a subscription for the given channel |
| unsubscribe | channel | Remove a subscription for a given channel |

Subscribe:

subscribe[space][channel]

unsubscribe[space][channel]

---------------------------------------------------------------
Room Subscription
---------------------------------------------------------------

subscribe[space]room:[room_name]
unsubscribe[space][room:[room_name]

Note: There's some form of room subscription limit (/backend/lib/game/socket/rooms.js) but I am
not sure if it's an over limit for the number of subscriptions a user can have or the number of
subscriptions a user may have for a single room. There is a USER_LIMIT variable that is currently
set to 2 so whether this means a user can subscribe to a maximum of 2 rooms or a user can have
up to 2 subscriptions to each room.

Need to read through the code again.

Either way if you reach that this while attempting to subscribe to a room the server will
response with the following:

["err@room:W9N1","subscribe limit reached"]

The data is a JSON array object with 2 string elements (it's also horrible). Element 0 is
the 'channel' (encoded with 'err@') and element 1 is the 'message'

Note: If the server supports shards the room name must be suffixed with a forward slash and the shard name.

E.g

subscribe room:W9N7/shard1
---------------------------------------------------------------
Console subscription
---------------------------------------------------------------

subscribe user:[username]/console


---------------------------------------------------------------
GZIP Compression
---------------------------------------------------------------
The server supports data compression via the GZip library which is
controlled via the 'gzip' command

gzip[space][on/off]

Example:

gzip on
gzip off

Note: Gzip compression is disabled by default

Once Gzip is enable all data received from the server from that point
on will be in the following format:

gz:[data]

Data will be base64 encoded.


------------------------------------------------------------------------------

[
  "room:W9N1",
  {
    "objects": {
      "7eef19e4741d288": {
        "name": "u1",
        "x": 27,
        "y": 7,
        "body": [
          {
            "type": "move",
            "hits": 100
          },
          {
            "type": "move",
            "hits": 100
          },
          {
            "type": "work",
            "hits": 100
          },
          {
            "type": "carry",
            "hits": 100
          }
        ],
        "energy": 0,
        "energyCapacity": 50,
        "type": "creep",
        "room": "W9N1",
        "user": "eea532c5a2f9e44",
        "hits": 400,
        "hitsMax": 400,
        "spawning": false,
        "fatigue": 0,
        "notifyWhenAttacked": true,
        "_id": "7eef19e4741d288",
        "meta": {
          "revision": 143,
          "created": 1543531022146,
          "version": 0,
          "updated": 1543533127853
        },
        "$loki": 2750,
        "ageTime": 48775,
        "actionLog": {
          "attacked": null,
          "healed": null,
          "attack": null,
          "rangedAttack": null,
          "rangedMassAttack": null,
          "rangedHeal": null,
          "harvest": null,
          "heal": null,
          "repair": null,
          "build": null,
          "say": null,
          "upgradeController": null,
          "reserveController": null
        }
      },
      "668b7e3df65bf80": {
        "structureType": "extension",
        "x": 34,
        "y": 5,
        "type": "constructionSite",
        "room": "W9N1",
        "user": "eea532c5a2f9e44",
        "progress": 2070,
        "progressTotal": 3000,
        "_id": "668b7e3df65bf80",
        "meta": {
          "revision": 414,
          "created": 1543367810917,
          "version": 0,
          "updated": 1543533172370
        },
        "$loki": 453
      },
      "a6f00771e7d3064": {
        "room": "W9N1",
        "type": "controller",
        "x": 43,
        "y": 27,
        "level": 2,
        "_id": "a6f00771e7d3064",
        "meta": {
          "revision": 7563,
          "created": 1477476556413,
          "version": 0,
          "updated": 1543533183801
        },
        "$loki": 23,
        "user": "eea532c5a2f9e44",
        "progress": 7717,
        "downgradeTime": 52783,
        "safeMode": 20001,
        "safeModeAvailable": 1
      },
      "cd9d0771e7d0ec8": {
        "room": "W9N1",
        "type": "source",
        "x": 23,
        "y": 5,
        "energy": 3000,
        "energyCapacity": 3000,
        "ticksToRegeneration": 300,
        "_id": "cd9d0771e7d0ec8",
        "meta": {
          "revision": 20553,
          "created": 1477476556413,
          "version": 0,
          "updated": 1543534205458
        },
        "$loki": 22,
        "nextRegenerationTime": null,
        "invaderHarvested": 41002
      },
      "fa330d29c943414": {
        "type": "extension",
        "x": 37,
        "y": 2,
        "room": "W9N1",
        "notifyWhenAttacked": true,
        "user": "eea532c5a2f9e44",
        "energy": 50,
        "energyCapacity": 50,
        "hits": 1000,
        "hitsMax": 1000,
        "_id": "fa330d29c943414",
        "meta": {
          "revision": 3,
          "created": 1543517674645,
          "version": 0,
          "updated": 1543517793095
        },
        "$loki": 2532,
        "off": false
      },
      "01cc7e3dafc0dfc": {
        "structureType": "extension",
        "x": 30,
        "y": 5,
        "type": "constructionSite",
        "room": "W9N1",
        "user": "eea532c5a2f9e44",
        "progress": 1430,
        "progressTotal": 3000,
        "_id": "01cc7e3dafc0dfc",
        "meta": {
          "revision": 286,
          "created": 1543367809788,
          "version": 0,
          "updated": 1543529982459
        },
        "$loki": 451
      },
      "5bda1b6d681993f": {
        "name": "u2",
        "x": 40,
        "y": 24,
        "body": [
          {
            "type": "move",
            "hits": 100
          },
          {
            "type": "move",
            "hits": 100
          },
          {
            "type": "work",
            "hits": 100
          },
          {
            "type": "carry",
            "hits": 100
          }
        ],
        "energy": 0,
        "energyCapacity": 50,
        "type": "creep",
        "room": "W9N1",
        "user": "eea532c5a2f9e44",
        "hits": 400,
        "hitsMax": 400,
        "spawning": false,
        "fatigue": 0,
        "notifyWhenAttacked": true,
        "_id": "5bda1b6d681993f",
        "meta": {
          "revision": 116,
          "created": 1543532631682,
          "version": 0,
          "updated": 1543533189871
        },
        "$loki": 2768,
        "ageTime": 49114,
        "actionLog": {
          "attacked": null,
          "healed": null,
          "attack": null,
          "rangedAttack": null,
          "rangedMassAttack": null,
          "rangedHeal": null,
          "harvest": null,
          "heal": null,
          "repair": null,
          "build": null,
          "say": null,
          "upgradeController": null,
          "reserveController": null
        }
      },
      "13757e3dafc2ab2": {
        "structureType": "extension",
        "x": 37,
        "y": 10,
        "type": "constructionSite",
        "room": "W9N1",
        "user": "eea532c5a2f9e44",
        "progress": 1075,
        "progressTotal": 3000,
        "_id": "13757e3dafc2ab2",
        "meta": {
          "revision": 215,
          "created": 1543367809788,
          "version": 0,
          "updated": 1543529971609
        },
        "$loki": 450
      },
      "635b1ab0f4f9118": {
        "name": "b1",
        "x": 31,
        "y": 4,
        "body": [
          {
            "type": "move",
            "hits": 100
          },
          {
            "type": "move",
            "hits": 100
          },
          {
            "type": "work",
            "hits": 100
          },
          {
            "type": "carry",
            "hits": 100
          }
        ],
        "energy": 0,
        "energyCapacity": 50,
        "type": "creep",
        "room": "W9N1",
        "user": "eea532c5a2f9e44",
        "hits": 400,
        "hitsMax": 400,
        "spawning": false,
        "fatigue": 0,
        "notifyWhenAttacked": true,
        "_id": "635b1ab0f4f9118",
        "meta": {
          "revision": 160,
          "created": 1543531859791,
          "version": 0,
          "updated": 1543533178213
        },
        "$loki": 2760,
        "ageTime": 48950,
        "actionLog": {
          "attacked": null,
          "healed": null,
          "attack": null,
          "rangedAttack": null,
          "rangedMassAttack": null,
          "rangedHeal": null,
          "harvest": null,
          "heal": null,
          "repair": null,
          "build": null,
          "say": null,
          "upgradeController": null,
          "reserveController": null
        }
      },
      "2d647e3dafc06e3": {
        "structureType": "extension",
        "x": 34,
        "y": 9,
        "type": "constructionSite",
        "room": "W9N1",
        "user": "eea532c5a2f9e44",
        "progress": 2390,
        "progressTotal": 3000,
        "_id": "2d647e3dafc06e3",
        "meta": {
          "revision": 478,
          "created": 1543367809788,
          "version": 0,
          "updated": 1543532834968
        },
        "$loki": 452
      },
      "0af332c5a34558c": {
        "type": "spawn",
        "room": "W9N1",
        "x": 33,
        "y": 6,
        "name": "Spawn1",
        "user": "eea532c5a2f9e44",
        "energy": 300,
        "energyCapacity": 300,
        "hits": 5000,
        "hitsMax": 5000,
        "spawning": null,
        "notifyWhenAttacked": false,
        "_id": "0af332c5a34558c",
        "meta": {
          "revision": 19512,
          "created": 1479132600884,
          "version": 0,
          "updated": 1543533066160
        },
        "$loki": 348,
        "off": false
      },
      "99a1191bb7bcf5f": {
        "name": "h2",
        "x": 32,
        "y": 5,
        "body": [
          {
            "type": "move",
            "hits": 100
          },
          {
            "type": "move",
            "hits": 100
          },
          {
            "type": "work",
            "hits": 100
          },
          {
            "type": "carry",
            "hits": 100
          }
        ],
        "energy": 28,
        "energyCapacity": 50,
        "type": "creep",
        "room": "W9N1",
        "user": "eea532c5a2f9e44",
        "hits": 400,
        "hitsMax": 400,
        "spawning": false,
        "fatigue": 0,
        "notifyWhenAttacked": true,
        "_id": "99a1191bb7bcf5f",
        "meta": {
          "revision": 267,
          "created": 1543530199931,
          "version": 0,
          "updated": 1543533066160
        },
        "$loki": 2741,
        "ageTime": 48581,
        "actionLog": {
          "attacked": null,
          "healed": null,
          "attack": null,
          "rangedAttack": null,
          "rangedMassAttack": null,
          "rangedHeal": null,
          "harvest": null,
          "heal": null,
          "repair": null,
          "build": null,
          "say": null,
          "upgradeController": null,
          "reserveController": null
        }
      },
      "56d76164cebb3f9": {
        "type": "mineral",
        "mineralType": "O",
        "mineralAmount": 60182.51069701724,
        "x": 15,
        "y": 25,
        "room": "W9N1",
        "_id": "56d76164cebb3f9",
        "meta": {
          "revision": 1,
          "created": 1477570874603,
          "version": 0,
          "updated": 1477570878171
        },
        "$loki": 263,
        "density": 2
      },
      "1c4318868f09c24": {
        "name": "h1",
        "x": 24,
        "y": 6,
        "body": [
          {
            "type": "move",
            "hits": 100
          },
          {
            "type": "move",
            "hits": 100
          },
          {
            "type": "work",
            "hits": 100
          },
          {
            "type": "carry",
            "hits": 100
          }
        ],
        "energy": 50,
        "energyCapacity": 50,
        "type": "creep",
        "room": "W9N1",
        "user": "eea532c5a2f9e44",
        "hits": 400,
        "hitsMax": 400,
        "spawning": false,
        "fatigue": 0,
        "notifyWhenAttacked": true,
        "_id": "1c4318868f09c24",
        "meta": {
          "revision": 395,
          "created": 1543529588976,
          "version": 0,
          "updated": 1543533207066
        },
        "$loki": 2730,
        "ageTime": 48373,
        "actionLog": {
          "attacked": null,
          "healed": null,
          "attack": null,
          "rangedAttack": null,
          "rangedMassAttack": null,
          "rangedHeal": null,
          "harvest": null,
          "heal": null,
          "repair": null,
          "build": null,
          "say": null,
          "upgradeController": null,
          "reserveController": null
        }
      }
    },
    "users": {
      "2": {
        "_id": "2",
        "username": "Invader"
      },
      "3": {
        "_id": "3",
        "username": "Source Keeper"
      },
      "eea532c5a2f9e44": {
        "username": "JackBot",
        "usernameLower": "jackbot",
        "cpu": 100,
        "gcl": 7917,
        "cpuAvailable": 10000,
        "registeredDate": "2016-11-14T14:10:00.879Z",
        "bot": "simplebot",
        "active": true,
        "badge": {
          "type": 12,
          "color1": "#166b9c",
          "color2": "#e1da64",
          "color3": "#b5fb01",
          "flip": false,
          "param": 26
        },
        "_id": "eea532c5a2f9e44",
        "meta": {
          "revision": 54009,
          "created": 1479132600880,
          "version": 0,
          "updated": 1543534353248
        },
        "$loki": 6,
        "lastUsedCpu": 13,
        "lastUsedDirtyTime": 31,
        "rooms": [
          "W9N1"
        ],
        "lastNotifyDate": 1543507254463,
        "blocked": false,
        "authTouched": true
      }
    },
    "flags": null,
    "info": {
      "mode": "world"
    }
  }
]
