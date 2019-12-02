# Screeps API
This file contains my notes on the Screeps game API

## REST API

### Base endpoint
The base end point for REST calls is formatted as follows:-

  <http|https>://<hosts>:<port>/api/

E.g

    https://screeps.com:443/api/

Note: The default port for private servers is 21025

#### Server Version
Retrieve information about the server.

Request:

  <rest-base-endpoint>/version

Response Body:

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

## Web Socket API
