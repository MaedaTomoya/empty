#define _HSV
#ifdef _HSV
#include"libOne.h"
void gmain() {
	window(1920, 1080, full);
	colorMode(HSV);
	float hue = 0;
	float satu = 255;
	float value = 255;
	while (notQuit) {
		if (isPress(KEY_Q)&& hue < 360) { hue += 5; }
		if (isPress(KEY_A)&& hue >0) { hue -= 5; }
		if (isPress(KEY_W) && hue < 360) { hue += 5; }
		if (isPress(KEY_S) && hue > 0) { hue += 5; }
		if (isPress(KEY_R) && satu < 255) { satu += 5; }
		if (isPress(KEY_F) && satu > 0) { satu += 5; }
		if (isPress(KEY_T) && value < 255) { value += 5; }
		if (isPress(KEY_G) && value > 0) { value += 5; }

		clear(0, 0, 0);
		fill(hue, satu, value);
		textSize(120);
		text((let)"hue=" + hue, 600, 400);
		text((let)"satu=" + satu, 600, 400);
		text((let)"value=" + value, 600, 400);
		int num = 12;
		float angle = hue / num;
		for (int i = 0; i < num; i++) {
			float px = cos(angle*i) * 200;
			float py = sin(angle*i) * 200;
			fill(angle * i, satu, value);
			noStroke();
			circle(1500-px, 540-py, 50);

		}

	}
}
#endif

#ifdef _SORT
#include"libOne.h"
void gmain() {
	window(1100, 1000);
	const int num = 20;
	int score[num];
	int r, c;
	for (int i = 0; i < num; i++) {
		score[i] = random() % 1000;
	}
	while (notQuit) {
		clear(60);
		if (isTrigger(KEY_A)){
			for (int i = 0; i < num; i++) {
				score[i] = random() % 1000;
			}
		}
		if (isTrigger(KEY_D)) {
			for (r = 0; r < num - 1; r++) {
				for (c = r + 1; c < num; c++) {
					if (score[r] < score[c]) {
						int w = score[r];
						score[r] = score[c];
						score[c] = w;
					}
				}
			}
		}
		for (int i = 0; i < num; i++) {
			print(score[i]);
			rect(100, 50 * i, score[i], 40);
		}
	}
}
#endif

#ifdef _SHOOT
#include"libOne.h"
void gmain() {
	window(1920, 1080, full);
	struct PLAYER {
		float px, py, w, h, vx, ofsY;
	};
	struct BULLET {
		float px, py, w, h, vy;
		int hp = 0;
	};
	struct PLAYER p;
	p.px = width / 2;
	p.py = height - 150;
	p.w = 100;
	p.h = 200;
	p.vx = 10;
	p.ofsY = -100;
	const int numBullets = 10;
	struct BULLET b[numBullets];
	for (int i = 0; i < numBullets; i++) {
	     b[i].px = p.px;
       	 b[i].py = p.py;
	     b[i].w = 10;
	     b[i].h = 20;
	     b[i].vy = -10;
	}
	while (notQuit) {
		if (isPress(KEY_A)) { p.px += -p.vx; }
		if (isPress(KEY_D)) { p.px += p.vx; }
		if (isTrigger(KEY_SPACE)) {
			for (int i = 0; i < numBullets; i++) {
				if (b[i].hp == 0) {
					b[i].hp = 1;
					b[i].px = p.px;
					b[i].py = p.py + p.ofsY;
					i = numBullets;
				}
			}
		}
		for (int i = 0; i < numBullets; i++){
			if (b[i].hp > 0) {
				b[i].py += b[i].vy;
				if (b[i].py < -b[i].h) {
					b[i].hp = 0;
				}
			}
	    } 
		clear();
		rectMode(CENTER);
		rect(p.px, p.py, p.w, p.h);
		for (int i = 0; i < numBullets; i++) {
			if (b[i].hp > 0) {
				rect(b[i].px, b[i].py, b[i].w, b[i].h);

			}
		}
	}

}
#endif

#ifdef _FACE
#include"libOne.h"
#include"face.h"
void gmain() {
	window(1920, 1080, full);
	float px = width / 2;
	float py = height / 2;
	float angle = 0;
	float ofsX = 100;
	float ofsY = 100;
	int sw = 1;
	while (notQuit) {
		ofsX = width / 2 - mouseX;
		ofsY = height / 2 - mouseY;
		if (isTrigger(KEY_SPACE)) { sw = 1 - sw; }
		angle += 0.01f;
		clear(60, 120, 240);
		strokeWeight(10);
		for(int i = -5; i <= 5; i++) {
			if (sw == 1) {
				roundface(px + ofsX * i, py + ofsY * i);
			}
			else {
				squareface(px + ofsX * i, py + ofsY * i, angle);
					
			}
		}
	}
}
#endif

#ifdef _HPゲージ
#include"libOne.h"
void gmain() {
	window(1920, 1080, full);
	//データ
	struct COLOR green = { 0,255,0 };
	struct COLOR yellow = { 255,255,0 };
	struct COLOR red = { 255,0,0 };
	struct COLOR color = green;


	int hpMax = 500;
	int hp = hpMax;
	int hpWarning = hpMax * 0.3f;
	int hpDanger = hpMax * 0.1f;
	float px = 700;
	float py = 200;
	float h = 60;
	while (notQuit) {
		if (isTrigger(KEY_SPACE)) { hp = hpMax; }
		if (hp > 0) { hp -= 2; }

		if (hp > hpWarning){
			color = green;
		}
		else if (hp > hpDanger){
			color = yellow;
		}
		else {
			color = red;
		}
		
		clear(74, 84, 89);
		fill(128);
		rect(px, py, hpMax, h);
		fill(color);
		rect(px, py, hp, h);
		if (hp <= 0) {
			textSize(100);
			fill(255, 0, 0);
			text("GameOver", 700, 400);
		}
	}
}
#endif

#ifdef _命の数
#include"libOne.h"
void gmain() {
	window(1920, 1080, full);
	//データ
	int life = 5;
	float px = 700;
	float py = 200;
	float radius = 50;
	float space = 100;
	while (notQuit) {
		//データ更新
		if (isTrigger(KEY_D)) { life++; }
		if (isTrigger(KEY_A)) { life--; }
		//描画
		clear(74, 84, 89); 

		fill(255, 255, 0);
		print((let)"life=" + life);
		
		strokeWeight(20);
		stroke(255);
		//whileバージョン
		int i = 0;
		fill(255, 200, 200);
		while (i < life) {
		   float offsetX = space * i;
		   circle(px + offsetX, py, radius * 2);
		   i++;
		}
		//forバージョン
		fill(160, 200, 240);
		for (int i = 0; i < life; i++){
			float offsetX = space * i;
			float offsetY = space * 2;
			circle(px + offsetX, py + offsetY, radius * 2);
			
		}

	}

}
#endif

#ifdef _if
#include"libOne.h"
void gmain() {
	window(1920,1080,full);
	float px = 1920 / 2;
	float py = 1080 / 2;
	float vx = 10;
	float radius = 150;
	float len = radius / 1.4142f * 2;
	float sw = radius / 8;
	float angle = 0;
	float angleSpeed = 0.03f;

	while (notQuit) {
	    px += vx;
		angle += angleSpeed;
		if (px < 0 || px > 1920) {
			vx = -vx;
			angleSpeed = -angleSpeed;
		}
		clear(60);
		strokeWeight(sw);
		stroke(255, 0, 0);
	    circle(px, py, radius * 2);
		rectMode(CENTER);
		rect(px, py, len, len,angle);
		strokeWeight(sw * 4);
		point(px, py);
		strokeWeight(sw);
		line(1920 / 2, 0, px, py);
	}
	
}
#endif

#ifdef _rect
#include"libOne.h"
void gmain() {
	window(1000, 1000);
	clear(200);

	strokeWeight(20);
	stroke(128);
	fill(140, 180, 220);

	rectMode(CENTER);
	angleMode(DEGREES);
	float px = 300, py = 200, w = 200, h = 300, angle = 45;
    rect(px, py, w, h, angle);

	pause();
}
#endif

#ifdef _circle
#include"libOne.h"
void gmain() {
	window(1000, 1000);
	clear(200);

	strokeWeight(20);
	stroke(230, 190, 140);
	fill(160, 200, 240);

	float px = 500, py = 500,radius = 200;
	circle(px, py, radius*2);
	
	pause();
}
#endif

#ifdef _line
#include"libOne.h"
void gmain() {
	window(1000, 1000);
	clear(255);
	strokeWeight(100);
	stroke(0, 255, 0);
	float sx = 100, sy = 500, ex = 900, ey = 600;
	line(sx, sy, ex, ey);
	line(500, 100, 500, 900);
	pause();
}
#endif

#ifdef _point
#include"libOne.h"
void gmain() {
	window(1000, 1000);
	clear(200);
	strokeWeight(40);
	stroke(255,0,0);
	point(500, 500);
	stroke(255, 255, 0);
	point(700, 500);
	stroke(0, 0, 255);
	point(900, 500);
	pause();
}
#endif

#ifdef _window&clear
#include"libOne.h"
void gmain() {
	window(800, 450);
	clear(180, 200, 170);
	pause();
}
#endif

#ifdef _introduction
#include"libOne.h"
void gmain() {
	window(800, 450,full);
	for (int j = 0; j < 9; j++) {
	  for (int i = 0; i < 16; i++) {
		  if ((j + i) % 2 == 0)fill(0);
		  else fill(0, 100, 0);
		  rect(50 * i, 50 * j, 50, 50);
	  }
	}

	pause();
}
#endif