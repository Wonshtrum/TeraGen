#include "view.h"

int main(void) {
		View view(640, 480, "Simple example");
		while (view.render()) {
		}
		exit(EXIT_SUCCESS);
}
