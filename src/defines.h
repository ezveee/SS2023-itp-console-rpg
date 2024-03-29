#pragma once

#define SCALE_FACTOR_X					1
#define SCALE_FACTOR_Y					1

/* not particularly necessary because of namespace mapConstants::mapElement
#define CORNER_BORDER					'+'
#define HORIZONTAL_BORDER				'-'
#define VERTICAL_BORDER					'|'
*/
#define THUMBNAIL_MAP_VILLAGE L"\n+-+\n|1|\n+-+\n|2|\n+-+\n"
#define THUMBNAIL_MAP_CITY_1 L"\n+-+-+-+\n|1|2|3|\n+-+-+-+\n|4|5|6|\n+-+-+-+\n"
#define THUMBNAIL_MAP_CITY_2 L"\n+-+-+\n|1|2|\n+-+-+\n|3|4|\n+-+-+\n"
#define THUMBNAIL_MAP_CITY_3 L"\n+-+\n|1|\n+-+-+\n|2|3|\n+-+-+\n"
#define THUMBNAIL_MAP_AREA_1 L"\n    +-+-+\n    |1|2|\n+-+-+-+-+\n|3|4|5|6|\n+-+-+-+-+\n"
#define THUMBNAIL_MAP_AREA_2 L"\n  +-+\n  |1|\n+-+-+\n|2|3|\n+-+-+\n|4|\n+-+-+-+\n|5|6|7|\n+-+-+-+\n|8|\n+-+\n"
#define THUMBNAIL_MAP_AREA_3 L"\n   +--+--+\n   | 1| 2|\n   +--+--+--+--+--+\n   | 3| 4| 5| 6| 7|\n+--+--+--+--+--+--+\n| 8| 9|10|11|\n+--+--+--+--+\n"
#define THUMBNAIL_MAP_AREA_4 L"\n+-+\n|1|\n+-+-+-+-+\n|2|3|4|5|\n+-+-+-+-+\n|6|7|\n+-+-+\n"
#define THUMBNAIL_MAP_DUNG_1 L"\n  +-+-+\n  |3|4|\n+-+-+-+\n|1|2|\n+-+-+\n"
#define THUMBNAIL_MAP_DUNG_2 L"\n+-+-+-+\n|1|2|3|\n+-+-+-+-+\n    |4|5|\n    +-+-+\n"
#define THUMBNAIL_MAP_DUNG_3 L"\n   +--+--+--+\n   | 1| 2| 3|\n   +--+--+--+\n   | 4| 5| 6|\n+--+--+--+--+\n| 7| 8| 9|10|\n+--+--+--+--+\n"

#define EMPTY_FIELD						' '
#define LANDMARK_DUNGEON				'D'
#define LANDMARK_HOUSE					'H'
#define LANDMARK_SHOP					'S'
#define LANDMARK_BLACKSMITH				'B'
#define LANDMARK_INN					'I'

#define PLAYER_CHAR						'X'
#define PLAYER_START_X					8
#define PLAYER_START_Y					10

#define ARROWKEY_UP						72
#define ARROWKEY_DOWN					80
#define ARROWKEY_LEFT					75
#define ARROWKEY_RIGHT					77
#define ESCAPEKEY						27

// TEMP probably different for every screen
#define MAP_SIZE_X						16
#define MAP_SIZE_Y						10
#define MAP_FIRST_GRAPHICS_LINE			0
#define MAP_FIRST_CONFIG_LINE			(MAP_SIZE_Y + 3)
#define MAP_FIRST_LEGEND_LINE			MAP_FIRST_CONFIG_LINE * 2
