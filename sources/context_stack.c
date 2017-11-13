
/*
 * machinarium.
 *
 * cooperative multitasking engine.
*/

#include <machinarium.h>
#include <machinarium_private.h>

#ifdef HAVE_VALGRIND
#  include <valgrind/valgrind.h>
#endif

int mm_contextstack_create(mm_contextstack_t *stack, size_t size)
{
	stack->size = size;
	stack->pointer = malloc(stack->size);
	if (stack->pointer == NULL)
		return -1;
#ifdef HAVE_VALGRIND
	stack->valgrind_stack =
		VALGRIND_STACK_REGISTER(stack->pointer, stack->pointer + stack->size);
#endif
	return 0;
}

void mm_contextstack_free(mm_contextstack_t *stack)
{
	if (stack->pointer == NULL)
		return;
#ifdef HAVE_VALGRIND
	VALGRIND_STACK_DEREGISTER(stack->valgrind_stack);
#endif
	free(stack->pointer);
}
