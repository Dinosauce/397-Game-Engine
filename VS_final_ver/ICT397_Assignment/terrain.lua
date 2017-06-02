Terrain = {

	
    
	TerrainFile = "3Dmodels/terrain/height128.raw",
	ImageSize = 128.0,
	ScaleFactor= {
    
		x = 10.0, 
		y = 1.0, 
		z = 10.0
    
	},
    
	HeightField = {
		iterations = 64,
		hSize = 128.0,
		minHeight = 1,
		maxHeight = 128,
		weight = 0.1,
		random = false
	},
	ProceduralTexture1 = "pictures/lowestTile.tga",
	ProceduralTexture2 = "pictures/lowTile.tga",
	ProceduralTexture3 = "pictures/highTile.tga",
	ProceduralTexture4 = "pictures/highestTile.tga",
	repeatnum = 1.0,
	textureMapping = true,
	DetailMap = "pictures/detailMap.tga",
	mapRepeat = 8.0,
	DetailMapping = true,
	LightMap = "pictures/lightmap.raw",
	LightMapSize = 128.0,
	LightMapping = true

	
}