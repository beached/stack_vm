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


enum class op_codes: size_t {
	halt = 0,
	nop,
	load,
	store,
	push,
	pop,
	port_out,
	port_in,
	add,
	sub,
	mul,
	div,
	binary_and,
	binary_or,
	binary_xor,
	binary_negate,
	shift_left,
	shift_right
};

struct stack_vm {
	std::vector<uint8_t> vm_memory;
	std::vector<size_t> vm_stack;
	std::vector<size_t> vm_return_stack;

	size_t vm_top_reg;
	size_t vm_prog_addr;

	stack_vm( size_t memory_size_bytes = 1024 ): vm_memory( memory_size_bytes, 0 ) { }
	stack_vm( std::vector<uint8_t> memory ): vm_memory{ std::move( memory ) } { }	

	size_t dispatch( ) const {
		assert( vm_prog_addr <= vm_memory_size( ) );
		return vm_memory[vm_prog_addr++];
	}

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
			
			case push:
				op_push( );
			break;
		
			case pop:
				op_pop( );
			break;
			
			case port_out:
				op_port_out( );
			break;
			
			case port_in:
				op_port_in( );
			break;
			
			case add:
				op_add( );
			break;
			
			case sub:
				op_sub( );
			break;
			
			case mul:
				op_mul( );
			break;
			
			case div:
				op_div( );
			break;
			
			case binary_and:
				op_binary_and( );
			break;
			
			case binary_or:
				op_binary_or( );
			break;
			
			case binary_xor:
				op_binary_xor( );
			break;
			
			case binary_negate:
				op_binary_negate( );
			break;
			
			case shift_left:
				op_shift_left( );
			break;
			
			case shift_right:
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
