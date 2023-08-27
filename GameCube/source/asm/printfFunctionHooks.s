# Hooking the printf functions with standard C++ functions is tedious due to variadic arguments, so handle the hooks via assembly
.global asm_handle_snprintf
.global asm_handle_vsnprintf

printf_invalid_params:
# Return 0 immediately
li %r3,0
blr

asm_handle_snprintf:
# Make sure the pointer to the buffer is valid
cmpwi %r3,0
beq- printf_invalid_params

# Make sure the size is valid
cmpwi %r4,0
ble- printf_invalid_params

# Restore the overwritten instruction
stwu %sp,-0xA0(%sp)
b snprintf + 0x4

asm_handle_vsnprintf:
# Make sure the pointer to the buffer is valid
cmpwi %r3,0
beq- printf_invalid_params

# Make sure the size is valid
cmpwi %r4,0
ble- printf_invalid_params

# Restore the overwritten instruction
stwu %sp,-0x20(%sp)
b vsnprintf + 0x4
