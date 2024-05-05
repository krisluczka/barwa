#include <iostream>
#include "script.h"

int main() {
	barwa::script kod;
	kod.load( "test.brw" );

	kod.run();
}