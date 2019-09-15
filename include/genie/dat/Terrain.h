/*
    geniedat - A library for reading and writing data files of genie
               engine games.
    Copyright (C) 2011 - 2013  Armin Preiml
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

#ifndef GENIE_TERRAIN_H
#define GENIE_TERRAIN_H
#include "genie/file/ISerializable.h"
#include "genie/dat/TerrainCommon.h"

namespace genie {

class Terrain : public SharedTerrain
{
public:
    Terrain();

    void setGameVersion(GameVersion gv) override;
    static unsigned short getTerrainCount(GameVersion gv);
    static void setTerrainCount(unsigned short cnt);

    int8_t IsWater = 0;
    int8_t HideInEditor = 0;
    int32_t StringID = 0;
    int16_t Phantom = 0;

    unsigned short getNameSize(void) override;

    int32_t BlendPriority = 0; //not in aoe/ror
    int32_t BlendType = 0; //not in aoe/ror

    std::pair<uint8_t, uint8_t> CliffColors = { 0, 0 };
    int8_t PassableTerrain = -1;
    int8_t ImpassableTerrain = -1;

    /// Tile Graphics: flat, 2 x 8 elevation, 2 x 1:1
    ///  Frame Count, Animations, Frame Index
    std::vector<FrameData> ElevationGraphics;

    int16_t TerrainToDraw = 0;
    std::pair<int16_t, int16_t> TerrainDimensions = { 0, 0 }; // rows + cols

    /// These refer to terrain borders, which are actually used only in AoE and RoR.
    std::vector<int16_t> Borders;

    static const unsigned short TERRAIN_UNITS_SIZE = 30;
    std::vector<int16_t> TerrainUnitID;
    std::vector<int16_t> TerrainUnitDensity;

    /// If two terrain units are to be placed on same spot, this selects which one will prevail others.
    /// 1 = prevails, others don't.
    /// Centralize
    /// 0   Place randomly on the tile
    /// 1   Place in middle of the tile
    std::vector<int8_t> TerrainUnitCentering;

    int16_t NumberOfTerrainUnitsUsed = 0;

private:
    static unsigned short terrain_count_;

    void serializeObject(void) override;
};
} // namespace genie

#endif // GENIE_TERRAIN_H
