// The MIT License (MIT)
//
// Copyright (c) 2013-2015 Darrell Wright
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files( the "Software" ), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <vector>
#include <cstdlib>
#include <cassert>

namespace op_codes {
	enum op_codes: size_t {
		halt = 0,
		nop = 1,
		load = 2,
		store = 3,
		push = 4,
		pop = 5,
		port_out = 6,
		port_in = 7,
		add = 8,
		sub = 9,
		mul = 10,
		div = 11,
		binary_and = 12,
		binary_or = 13,
		binary_xor = 14,
		binary_negate = 15,
		shift_left = 16,
		shift_right = 17
	};
}	// namespace op_codes

struct stack_vm {
	std::vector<uint8_t> vm_memory;
	std::vector<size_t> vm_stack;
	std::vector<size_t> vm_return_stack;

	size_t vm_top_reg;
	size_t vm_prog_addr;

	stack_vm( size_t memory_size_bytes = 1024 ): vm_memory( memory_size_bytes, 0 ), vm_top_reg{ 0 }, vm_prog_addr{ 0 } { }

	stack_vm( std::vector<uint8_t> memory, size_t prog_addr = 0 ): vm_memory { std::move( memory ) }, vm_top_reg { 0 }, vm_prog_addr { prog_addr } { }

	size_t dispatch( ) {
		assert( vm_prog_addr <= vm_memory.size( ) );
		return vm_memory[vm_prog_addr++];
	}

	void op_halt( ) { }

	void op_nop( ) { }

	void op_load( ) { }

	void op_push( ) { }

	void op_pop( ) { }

	void op_port_out( ) { }

	void op_port_in( ) { }

	void op_add( ) { }

	void op_sub( ) { }

	void op_mul( ) { }

	void op_div( ) { }

	void op_binary_and( ) { }

	void op_binary_or( ) { }

	void op_binary_xor( ) { }

	void op_binary_negate( ) { }

	void op_shift_left( ) { }

	void op_shift_right( ) { }

	void step( ) {
		switch( dispatch( ) ) {
			case op_codes::halt:
				op_halt( );
			break;

			case op_codes::nop:
				op_nop( );
			break;

			case op_codes::load:
				op_load( );	
			break;
			
			case op_codes::push:
				op_push( );
			break;
		
			case op_codes::pop:
				op_pop( );
			break;
			
			case op_codes::port_out:
				op_port_out( );
			break;
			
			case op_codes::port_in:
				op_port_in( );
			break;
			
			case op_codes::add:
				op_add( );
			break;
			
			case op_codes::sub:
				op_sub( );
			break;
			
			case op_codes::mul:
				op_mul( );
			break;
			
			case op_codes::div:
				op_div( );
			break;
			
			case op_codes::binary_and:
				op_binary_and( );
			break;
			
			case op_codes::binary_or:
				op_binary_or( );
			break;
			
			case op_codes::binary_xor:
				op_binary_xor( );
			break;
			
			case op_codes::binary_negate:
				op_binary_negate( );
			break;
			
			case op_codes::shift_left:
				op_shift_left( );
			break;
			
			case op_codes::shift_right:
				op_shift_right( );
			break;
			
			default:
				throw std::runtime_error( "Invalid opcode" );
		}
	}
	
};

int main( int argc, char** argv ) {

	return EXIT_SUCCESS;
}
