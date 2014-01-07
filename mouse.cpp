#include "mouse.h"

mouse::mouse(void)
{
	if(!al_is_mouse_installed()) {
		al_install_mouse();
	}
	buttons_down = new bool[al_get_mouse_num_buttons()-1];
	buttons_pressed = new bool[al_get_mouse_num_buttons()-1];
	for(unsigned int i = 0; i <al_get_mouse_num_buttons()-1; i++) {
		buttons_down[i] = buttons_pressed[i] = false;
	}
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_mouse_event_source());
	x = y = z = w = dx = dy = dz = dw = mousex = mousey = 0;
	display = NULL;
}


mouse::~mouse(void)
{
	delete[] buttons_down;
	delete[] buttons_pressed;
	al_destroy_event_queue(queue);
}

bool mouse::poll(ALLEGRO_EVENT& ev) {
	ALLEGRO_EVENT event;
	if(!al_get_next_event(queue, &event)) {
		ev = event;
		return false;
	}
	else {
		ev = event;
		switch (event.type) {
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			buttons_pressed[event.mouse.button-1] = true;
			buttons_down[event.mouse.button-1] = true;
		break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			buttons_pressed[event.mouse.button-1] = false;
			buttons_down[event.mouse.button-1] = false;
		break;
		case ALLEGRO_EVENT_MOUSE_AXES:
			x = event.mouse.x;
			y = event.mouse.y;
			z = event.mouse.z;
			w = event.mouse.w;
			dx += event.mouse.dx;
			dy += event.mouse.dy;
			dz += event.mouse.dz;
			dw += event.mouse.dw;
		break;
		case ALLEGRO_EVENT_MOUSE_WARPED:
			x = event.mouse.x;
			y = event.mouse.y;
			z = event.mouse.z;
			w = event.mouse.w;
		break;
		case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
			if(display) {
				al_set_mouse_xy(display, mousex, mousey);
			}
		break;
		}
		return true;
	}
}

void mouse::catch_mouse(ALLEGRO_DISPLAY* disp, int mx, int my) {
	display = disp;
	mousex = mx;
	mousey = my;
}

void mouse::uncatch_mouse() {
	display = NULL;
	mousex = mousey = 0;
}

bool mouse::button_down(unsigned int button) {
	if(button > al_get_mouse_num_buttons() || button < 1) {
		return false;
	}
	else {
		ALLEGRO_EVENT ev;
		while(poll(ev)) {
			al_rest(0.005);
		}
		return buttons_down[button-1];
	}
}

bool mouse::button_pressed(unsigned int button) {
	if(button > al_get_mouse_num_buttons() || button < 1) {
		return false;
	}
	else {
		ALLEGRO_EVENT ev;
		while(poll(ev)) {
			al_rest(0.005);
		}
		bool val = buttons_pressed[button-1];
		buttons_pressed[button-1] = false;
		return val;
	}
}

int mouse::get_x() {
	ALLEGRO_EVENT ev;
	while(poll(ev)) {
		al_rest(0.005);
	}
	return x;
}

int mouse::get_y() {
	ALLEGRO_EVENT ev;
	while(poll(ev)) {
		al_rest(0.005);
	}
	return y;
}

int mouse::get_z() {
	ALLEGRO_EVENT ev;
	while(poll(ev)) {
		al_rest(0.005);
	}
	return z;
}

int mouse::get_w() {
	ALLEGRO_EVENT ev;
	while(poll(ev)) {
		al_rest(0.005);
	}
	return w;
}

int mouse::get_dx() {
	ALLEGRO_EVENT ev;
	while(poll(ev)) {
		al_rest(0.005);
	}
	int val = dx;
	dx = 0;
	return val;
}

int mouse::get_dy() {
	ALLEGRO_EVENT ev;
	while(poll(ev)) {
		al_rest(0.005);
	}
	int val = dy;
	dy = 0;
	return val;
}

int mouse::get_dz() {
	ALLEGRO_EVENT ev;
	while(poll(ev)) {
		al_rest(0.005);
	}
	int val = dz;
	dz = 0;
	return val;
}

int mouse::get_dw() {
	ALLEGRO_EVENT ev;
	while(poll(ev)) {
		al_rest(0.005);
	}
	int val = dw;
	dw = 0;
	return val;
}

void mouse::get_xy(int& mx, int& my) {
	ALLEGRO_EVENT ev;
	while(poll(ev)) {
		al_rest(0.005);
	}
	mx= x;
	my = y;
}

void mouse::get_zw(int& mz, int& mw) {
	ALLEGRO_EVENT ev;
	while(poll(ev)) {
		al_rest(0.005);
	}
	mz = z;
	mw = w;
}

void mouse::get_dx_dy(int& mdx, int& mdy) {
	ALLEGRO_EVENT ev;
	while(poll(ev)) {
		al_rest(0.005);
	}
	int val = dx;
	dx = 0;
	mdx = val;
	val = dy;
	dy = 0;
	mdy = val;
}

void mouse::get_dz_dw(int& mdz, int& mdw) {
	ALLEGRO_EVENT ev;
	while(poll(ev)) {
		al_rest(0.005);
	}
	int val = dz;
	dz = 0;
	mdz = val;
	val = dw;
	dw = 0;
	mdw = val;
}

void mouse::get_axes(int& mx, int& my, int& mz, int& mw) {
	ALLEGRO_EVENT ev;
	while(poll(ev)) {
		al_rest(0.005);
	}
	mx = x;
	my = y;
	mz = z;
	mw = w;
}

void mouse::get_changes(int& mdx, int& mdy, int& mdz, int& mdw) {
	ALLEGRO_EVENT ev;
	while(poll(ev)) {
		al_rest(0.005);
	}
	int val = dx;
	dx = 0;
	mdx = val;
	val = dy;
	dy = 0;
	mdy = val;
	val = dz;
	dz = 0;
	mdz = val;
	val = dw;
	dw = 0;
	mdw = val;
}
