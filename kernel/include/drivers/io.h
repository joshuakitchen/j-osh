#ifndef HGUARD_IO
#define HGUARD_IO

#include "../types.h"

/// <summary>
/// Reads a byte from a specified IO port.
/// </summary>
///
/// <param name="port">The port to read from</param>
/// <return>The byte just read.</return>
u8 port_byte_in(u16 port);

/// <summary>
/// Writes a byte to a specified IO port.
/// </summary>
///
/// <param name="port">The port to write to</param>
/// <param name="data">The data to write</param>
void port_byte_out(u16 port, u8 data);

/// <summary>
/// Reads a word from a specified IO port.
/// </summary>
///
/// <param name="port">The port to read from</param>
/// <return>The word just read.</return>
u16 port_word_in(u16 port);

/// <summary>
/// Writes a word to a specified IO port.
/// </summary>
///
/// <param name="port">The port to write to</param>
/// <param name="data">The data to write</param>
void port_word_out(u16 port, u16 data);

#endif
