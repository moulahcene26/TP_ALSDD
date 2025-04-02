/------/File Structure :/------/

    TP2.c → Main program.

    visual.h → Displays ASCII art (not important for logic).

    logic.h → Handles city data and pathfinding.

    data.csv → Stores city connections.

/------/How Data is Organized (data.csv)** :/------/

  CityName,ConnectedCity1:Distance
  CityName,ConnectedCity2:Distance ...


       * City1 is connected to:
            |
            - City2 with a distance of 260
            |
            - City4 with a distance of 110

       * City2 is connected to City3 with a distance of 400

       * City3 has no listed connections.

       * City4 is connected to:
            |
            -City3 with a distance of 350
            |
            -City2 with a distance of 100