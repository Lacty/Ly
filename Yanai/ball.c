int x = 0, y = 0;
int vx = 2, vy = 2;

void setup() {
	size(500, 500);
}

void draw() {
	background(255, 255, 0);
	ellipse(x, y, 20, 20);
	x += vx; y += vy;
	if (x < 0 || width < x) {
		vx *= -1;
	}
	if (y < 0 || height < y) {
		vy *= -1;
	}
}