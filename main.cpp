#include <raylib.h>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

const int TRACK_DIST = 120;
const int SWITCH_DIST = 80;

int OFFSET_TRACK;
int OFFSET_SWITCH;

enum TrackDir {
	STRAGHT = 0,
	LEFT = 1,
	RIGHT = 2
};

struct TrackSwitch {
	TrackDir dir;
	bool can_switch = true;
};

vector<vector<TrackSwitch>> tracks;

int switches = 3;
int track_count = 4;

int score = 0;
int mistakes = 0;

bool paused = false;
bool game_over = false;

class Train {
	public:
	int track;
	int dest_track;
	int xpos;
	int position;
	void Draw() {
		Color col = ColorFromHSV(360.0f/track_count*dest_track, 0.8f, 0.9f);
		DrawRectangle(xpos,position,25,25,col);
	};
	void Update() {
		position += 1;
		int s = (position - OFFSET_SWITCH);
		if (s%SWITCH_DIST == 0){
			if (tracks[track].size() >= s/SWITCH_DIST)
			switch (tracks[track][s/SWITCH_DIST].dir) {
				case LEFT:
					track--;
					break;
				case RIGHT:
					track++;
					break;
				default:
					break;
			}
		}
		int pos = OFFSET_TRACK+track*TRACK_DIST;
		if (xpos != pos) xpos += 3 * ((xpos - pos) > 0 ? -1 : 1);
	};
	Train(int tr, int dtr){
		track = tr;
		dest_track = dtr;
		position = -25;
		xpos = OFFSET_TRACK+tr*TRACK_DIST; 
	}
};

vector<Train> trains;

class {
	public:
	int index_x = 0;
	int index_y = 0;
	void Update() {
		int ix = 0;
		int iy = 0;

        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) ix += 1;
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) ix -= 1;
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) iy -= 1;
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) iy += 1;
		
		index_x += ix;
		index_y += iy;
		
		if (index_x >= track_count) index_x = 0;
		if (index_x < 0) index_x = track_count - 1;
		if (index_y >= switches) index_y = 0;
		if (index_y < 0) index_y = switches - 1;



		if (IsKeyPressed(KEY_ENTER)) {
			TrackDir dir = tracks[index_x][index_y].dir;
			switch (dir) {
				case STRAGHT:
					dir = index_x == 0 ? RIGHT : LEFT;
					break;
				case LEFT:
					dir = index_x == track_count-1 ? STRAGHT : RIGHT;
					break;
				case RIGHT:
					dir = STRAGHT;
					break;
			}
			tracks[index_x][index_y].dir = dir;
		}
		TrackDir &dir = tracks[index_x][index_y].dir;
		if (IsKeyPressed(KEY_J)) if (index_x > 0) dir = LEFT;
		if (IsKeyPressed(KEY_K)) dir = STRAGHT;
		if (IsKeyPressed(KEY_L)) if (index_x < track_count - 1) dir = RIGHT;
	};
	void Draw() {
		DrawCircle(OFFSET_TRACK+index_x*TRACK_DIST,OFFSET_SWITCH+index_y*SWITCH_DIST,12,RED);
	};

} cursor;

void InitTracks(){
	for (int i = 0; i < track_count; i++) {
		vector<TrackSwitch> track;
		for (int j = 0; j < switches; j++) {
			TrackSwitch s;
			track.push_back(s);
		}
		tracks.push_back(track);
	}
}


void DrawTracks(){
	for (int i = 0; i < track_count; i++) {
		for (int j = 0; j < switches; j++) {
			Color col = BLACK;
			switch (tracks[i][j].dir) {
				case STRAGHT:
					col = BLACK;
					break;
				case LEFT:
					col = PURPLE;
					break;
				case RIGHT:
					col = GREEN;
					break;
			}
			DrawRectangle(OFFSET_TRACK+i*TRACK_DIST,OFFSET_SWITCH+j*SWITCH_DIST,25,25,col);
		}
	}
}

void CalculateSizeConstants()
{
    int total_tracks_width = (track_count - 1) * TRACK_DIST;
    int total_switches_height = (switches - 1) * SWITCH_DIST;
	OFFSET_TRACK  = (GetScreenWidth()  - total_tracks_width)  / 2;
	OFFSET_SWITCH = (GetScreenHeight() - total_switches_height) / 2;
}


void Update() {
	if (IsKeyPressed(KEY_P) && !game_over) paused = !paused;
	if (game_over || paused) {
	} else {
		int i = 0;
		while (i < trains.size()){
			Train &t = trains[i];
			t.Update();
			if (t.position > GetScreenHeight() - 60) {
				if (t.track == t.dest_track) {
					score++;
				}
				else {
					mistakes++; 
					if (mistakes >= 3) game_over = true;
				}
				trains.erase(trains.begin()+i);
				trains.push_back(Train(rand()%4, rand()%4));
			} else {
				i++;
			}
		}
		cursor.Update();
	}
}

void Draw() {

    BeginDrawing();
		
		ClearBackground(RAYWHITE);

		DrawTracks();

		for (auto &t : trains) {
			t.Draw();
		}

		cursor.Draw();
		
		for (int i = 0; i < track_count; i++) {
			Color col = ColorFromHSV(360.0f/track_count*i, 0.8f, 0.9f);
			DrawRectangle(OFFSET_TRACK+i*TRACK_DIST,400,25,25,col);
		}
		
		DrawText(TextFormat("Score: %d", score), 20, 20, 24, BLACK);
		for (int i = 0; i < mistakes; i++)
			DrawText("x", 20+i*30, 46, 36, RED);

		if (game_over) {
			DrawText("GAME OVER", 50,180, 20, GRAY);
		} else if (paused) {
			DrawText("PAUSED", 50,180, 20, GRAY);
		}

	EndDrawing();
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Train game");

    SetTargetFPS(60);

	srand(time(0));

	CalculateSizeConstants();

	InitTracks();

	trains.push_back(Train(rand()%4, rand()%4));


    while (!WindowShouldClose())
    {
		Update();
    	Draw();
	}

    CloseWindow();

    return 0;
}
