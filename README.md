# Screep Studio

Screep Studio is a native cross platform client for the [Screeps](https://screeps.com/) MMO sandbox game for programmers.
It is written using the Qt Cross Platform C++ framework so should compile and run on Microsoft Windows, Mac OS and Linux.

Note: Screep Studio is currently in development (on an ad-hoc basis) so it is far from complete. While it can successfully
connect to either a privately hosted server or the live Screeps server (probably not a great idea but the client is reasonably
stable and shouldn't doing anything that might cause problems for the server) there is currently no UI for selecting a server,
logging on or opening rooms, for the moment this is hard-coded in [ScreepStudioApplication.cpp](ScreepStudioApplication.cpp)

Features:

- Supports opening multiple rooms (Note: The live server currently on allows two room subscriptions but private servers can be modified
  to remove this restriction)
- Basic rendering for the following game entities
    Construction Sites,
    Containers,
    Controllers,
    Creeps,
    Energy Deposits,
    Extensions,
    Extractors,
    Labs,
    Links,
    Minerals,
    Nukers,
    Observers,
    Power Spawns,
    Ramparts,
    Roads,
    Sources,
    Spwans,
    Storage,
    Terminals,
    Tombstones,
    Towers,
    Walls
    Unknown (placeholder shown when the entity is not supported)


Know Issues:

Example screenshot 1
![Screep Studio](screenshots/screep-studio-001.png)

Example screenshot 2
![Screep Studio](screenshots/screep-studio-002.png)
