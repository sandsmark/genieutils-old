/*
    genie/dat - A library for reading and writing data files of genie
               engine games.
    Copyright (C) 2011 - 2017  Mikko "Tapsa" P

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "genie/dat/RandomMap.h"

namespace genie {

//------------------------------------------------------------------------------
void RandomMaps::setGameVersion(GameVersion gv)
{
    ISerializable::setGameVersion(gv);

    updateGameVersion(Maps);
}

//------------------------------------------------------------------------------
void RandomMaps::serializeObject()
{
    uint32_t random_map_count{};

    if (getGameVersion() < GV_AoEB) {
        serializeSize<uint32_t>(random_map_count, OldMaps.size());

        if (isOperation(OP_READ)) {
            OldMaps.resize(random_map_count);
        }

        for (std::vector<int32_t> &sub : OldMaps) {
            serialize<int32_t>(sub, 852);
        }
    } else {
        serializeSize<uint32_t>(random_map_count, Maps.size());

        serialize<int32_t>(RandomMapsPtr);

        serialize(Maps, random_map_count);
        serialize(Maps, random_map_count);
    }
}

//------------------------------------------------------------------------------
void MapInfo::setGameVersion(GameVersion gv)
{
    ISerializable::setGameVersion(gv);

    updateGameVersion(MapLands);
    updateGameVersion(MapTerrains);
    updateGameVersion(MapUnits);
    updateGameVersion(MapElevations);
}

//------------------------------------------------------------------------------
void MapInfo::serializeObject(void)
{
    if (!io_all_) {
        serialize<int32_t>(MapID);
    }

    // Yes. These are read and written twice.

    serialize<int32_t>(BorderSouthWest);
    serialize<int32_t>(BorderNorthWest);
    serialize<int32_t>(BorderNorthEast);
    serialize<int32_t>(BorderSouthEast);
    serialize<int32_t>(BorderUsage);
    serialize<int32_t>(WaterShape);
    serialize<int32_t>(BaseTerrain);
    serialize<int32_t>(LandCoverage);
    serialize<int32_t>(UnusedID);

    uint32_t count = 0;
    serializeSize<uint32_t>(count, MapLands.size());
    serialize<int32_t>(MapLandsPtr);

    if (io_all_) {
        serialize(MapLands, count);
    }

    serializeSize<uint32_t>(count, MapTerrains.size());
    serialize<int32_t>(MapTerrainsPtr);

    if (io_all_) {
        serialize(MapTerrains, count);
    }

    serializeSize<uint32_t>(count, MapUnits.size());
    serialize<int32_t>(MapUnitsPtr);

    if (io_all_) {
        serialize(MapUnits, count);
    }

    serializeSize<uint32_t>(count, MapElevations.size());
    serialize<int32_t>(MapElevationsPtr);

    if (io_all_) {
        serialize(MapElevations, count);
    }

    io_all_ = !io_all_;
}

//------------------------------------------------------------------------------
void MapLand::setGameVersion(GameVersion gv)
{
    ISerializable::setGameVersion(gv);
}

//------------------------------------------------------------------------------
void MapLand::serializeObject(void)
{
    serialize<int32_t>(LandID);
    serialize<int32_t>(Terrain); //int8_t
    serialize<int32_t>(LandSpacing);
    serialize<int32_t>(BaseSize);
    serialize<int8_t>(Zone);
    serialize<int8_t>(PlacementType);
    serialize<int16_t>(Padding1);
    serialize<int32_t>(BaseX);
    serialize<int32_t>(BaseY);
    serialize<int8_t>(LandProportion);
    serialize<int8_t>(ByPlayerFlag);
    serialize<int16_t>(Padding2);
    serialize<int32_t>(StartAreaRadius);
    serialize<int32_t>(TerrainEdgeFade);
    serialize<int32_t>(Clumpiness);
}

//------------------------------------------------------------------------------
void MapTerrain::setGameVersion(GameVersion gv)
{
    ISerializable::setGameVersion(gv);
}

//------------------------------------------------------------------------------
void MapTerrain::serializeObject(void)
{
    serialize<int32_t>(Proportion);
    serialize<int32_t>(Terrain);
    serialize<int32_t>(ClumpCount);
    serialize<int32_t>(EdgeSpacing);
    serialize<int32_t>(PlacementTerrain);
    serialize<int32_t>(Clumpiness);
}

//------------------------------------------------------------------------------
void MapUnit::setGameVersion(GameVersion gv)
{
    ISerializable::setGameVersion(gv);
}

//------------------------------------------------------------------------------
void MapUnit::serializeObject(void)
{
    serialize<int32_t>(Unit);
    serialize<int32_t>(HostTerrain);
    serialize<int8_t>(GroupPlacing);
    serialize<int8_t>(ScaleFlag);
    serialize<int16_t>(Padding1);
    serialize<int32_t>(ObjectsPerGroup);
    serialize<int32_t>(Fluctuation);
    serialize<int32_t>(GroupsPerPlayer);
    serialize<int32_t>(GroupArea);
    serialize<int32_t>(PlayerID);
    serialize<int32_t>(SetPlaceForAllPlayers);
    serialize<int32_t>(MinDistanceToPlayers);
    serialize<int32_t>(MaxDistanceToPlayers);
}

//------------------------------------------------------------------------------
void MapElevation::setGameVersion(GameVersion gv)
{
    ISerializable::setGameVersion(gv);
}

//------------------------------------------------------------------------------
void MapElevation::serializeObject(void)
{
    serialize<int32_t>(Proportion);
    serialize<int32_t>(Terrain);
    serialize<int32_t>(ClumpCount);
    serialize<int32_t>(BaseTerrain);
    serialize<int32_t>(BaseElevation);
    serialize<int32_t>(TileSpacing);
}
} // namespace genie
