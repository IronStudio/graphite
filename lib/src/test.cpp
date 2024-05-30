#include "test.hpp"

#include <iostream>


namespace gr {
	void sayHello() {
		#ifdef GR_WINDOWS
			std::cout << "Hello from Windows testlib !" << std::endl;
		#elifdef GR_LINUX
			std::cout << "Hello from Linux testlib !" << std::endl;
		#elifdef GR_APPLE
			std::cout << "Hello from Apple testlib !" << std::endl;
		#endif
	}
}