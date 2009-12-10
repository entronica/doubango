
/* #line 1 "tsip_parser_header_CSeq.rl" */
/*
* Copyright (C) 2009 Mamadou Diop.
*
* Contact: Mamadou Diop <diopmamadou@yahoo.fr>
*	
* This file is part of Open Source Doubango Framework.
*
* DOUBANGO is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*	
* DOUBANGO is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*	
* You should have received a copy of the GNU General Public License
* along with DOUBANGO.
*
*/

/**@file tsip_header_CSeq.c
 * @brief SIP CSeq header.
 *
 * @author Mamadou Diop <diopmamadou(at)yahoo.fr>
 *
 * @date Created: Sat Nov 8 16:54:58 2009 mdiop
 */
#include "tinysip/headers/tsip_header_CSeq.h"

#include "tinysip/parsers/tsip_parser_uri.h"

#include "tsk_debug.h"
#include "tsk_memory.h"

/**@defgroup tsip_header_CSeq_group SIP 'CSeq' header.
*/

/***********************************
*	Ragel state machine.
*/

/* #line 77 "tsip_parser_header_CSeq.rl" */




tsip_header_CSeq_t *tsip_header_CSeq_parse(const char *data, size_t size)
{
	int cs = 0;
	const char *p = data;
	const char *pe = p + size;
	const char *eof = pe;
	tsip_header_CSeq_t *hdr_cseq = TSIP_HEADER_CSEQ_CREATE();
	
	const char *tag_start;

	
/* #line 63 "../source/headers/tsip_header_CSeq.c" */
static const char _tsip_machine_parser_header_CSeq_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3
};

static const char _tsip_machine_parser_header_CSeq_key_offsets[] = {
	0, 0, 2, 4, 6, 8, 11, 16, 
	17, 19, 23, 28, 45, 46, 48, 64, 
	79, 80
};

static const char _tsip_machine_parser_header_CSeq_trans_keys[] = {
	67, 99, 83, 115, 69, 101, 81, 113, 
	9, 32, 58, 9, 13, 32, 48, 57, 
	10, 9, 32, 9, 32, 48, 57, 9, 
	13, 32, 48, 57, 9, 13, 32, 33, 
	37, 39, 126, 42, 43, 45, 46, 48, 
	57, 65, 90, 95, 122, 10, 9, 32, 
	9, 32, 33, 37, 39, 126, 42, 43, 
	45, 46, 48, 57, 65, 90, 95, 122, 
	13, 33, 37, 39, 126, 42, 43, 45, 
	46, 48, 57, 65, 90, 95, 122, 10, 
	0
};

static const char _tsip_machine_parser_header_CSeq_single_lengths[] = {
	0, 2, 2, 2, 2, 3, 3, 1, 
	2, 2, 3, 7, 1, 2, 6, 5, 
	1, 0
};

static const char _tsip_machine_parser_header_CSeq_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 1, 0, 
	0, 1, 1, 5, 0, 0, 5, 5, 
	0, 0
};

static const char _tsip_machine_parser_header_CSeq_index_offsets[] = {
	0, 0, 3, 6, 9, 12, 16, 21, 
	23, 26, 30, 35, 48, 50, 53, 65, 
	76, 78
};

static const char _tsip_machine_parser_header_CSeq_indicies[] = {
	0, 0, 1, 2, 2, 1, 3, 3, 
	1, 4, 4, 1, 4, 4, 5, 1, 
	5, 6, 5, 7, 1, 8, 1, 9, 
	9, 1, 9, 9, 7, 1, 10, 11, 
	10, 12, 1, 13, 14, 13, 15, 15, 
	15, 15, 15, 15, 15, 15, 15, 1, 
	16, 1, 17, 17, 1, 17, 17, 15, 
	15, 15, 15, 15, 15, 15, 15, 15, 
	1, 18, 19, 19, 19, 19, 19, 19, 
	19, 19, 19, 1, 20, 1, 1, 0
};

static const char _tsip_machine_parser_header_CSeq_trans_targs[] = {
	2, 0, 3, 4, 5, 6, 7, 10, 
	8, 9, 11, 12, 10, 11, 12, 15, 
	13, 14, 16, 15, 17
};

static const char _tsip_machine_parser_header_CSeq_trans_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 1, 
	0, 0, 5, 5, 0, 0, 0, 1, 
	0, 0, 3, 0, 7
};

static const int tsip_machine_parser_header_CSeq_start = 1;
static const int tsip_machine_parser_header_CSeq_first_final = 17;
static const int tsip_machine_parser_header_CSeq_error = 0;

static const int tsip_machine_parser_header_CSeq_en_main = 1;


/* #line 92 "tsip_parser_header_CSeq.rl" */
	
/* #line 141 "../source/headers/tsip_header_CSeq.c" */
	{
	cs = tsip_machine_parser_header_CSeq_start;
	}

/* #line 93 "tsip_parser_header_CSeq.rl" */
	
/* #line 148 "../source/headers/tsip_header_CSeq.c" */
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_keys = _tsip_machine_parser_header_CSeq_trans_keys + _tsip_machine_parser_header_CSeq_key_offsets[cs];
	_trans = _tsip_machine_parser_header_CSeq_index_offsets[cs];

	_klen = _tsip_machine_parser_header_CSeq_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _tsip_machine_parser_header_CSeq_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += ((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _tsip_machine_parser_header_CSeq_indicies[_trans];
	cs = _tsip_machine_parser_header_CSeq_trans_targs[_trans];

	if ( _tsip_machine_parser_header_CSeq_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _tsip_machine_parser_header_CSeq_actions + _tsip_machine_parser_header_CSeq_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
/* #line 50 "tsip_parser_header_CSeq.rl" */
	{
		TSK_DEBUG_INFO("CSEQ:TAG");
		tag_start = p;
	}
	break;
	case 1:
/* #line 56 "tsip_parser_header_CSeq.rl" */
	{
		PARSER_SET_STRING(hdr_cseq->method);
		TSK_DEBUG_INFO("CSEQ:PARSE_METHOD");
	}
	break;
	case 2:
/* #line 62 "tsip_parser_header_CSeq.rl" */
	{
		PARSER_SET_INTEGER(hdr_cseq->seq);
		TSK_DEBUG_INFO("CSEQ:PARSE_SEQ");
	}
	break;
	case 3:
/* #line 68 "tsip_parser_header_CSeq.rl" */
	{
		TSK_DEBUG_INFO("CSEQ:EOB");
	}
	break;
/* #line 249 "../source/headers/tsip_header_CSeq.c" */
		}
	}

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

/* #line 94 "tsip_parser_header_CSeq.rl" */
	
	if( cs < 
/* #line 265 "../source/headers/tsip_header_CSeq.c" */
17
/* #line 95 "tsip_parser_header_CSeq.rl" */
 )
	{
		TSIP_HEADER_CSEQ_SAFE_FREE(hdr_cseq);
	}
	
	return hdr_cseq;
}







//========================================================
//	CSeq header object definition
//

/**@ingroup tsip_header_CSeq_group
*/
static void* tsip_header_CSeq_create(void *self, va_list * app)
{
	tsip_header_CSeq_t *CSeq = self;
	if(CSeq)
	{
		CSeq->type = tsip_htype_CSeq;
		CSeq->seq = -1;
	}
	else
	{
		TSK_DEBUG_ERROR("Failed to create new CSeq header.");
	}
	return self;
}

/**@ingroup tsip_header_CSeq_group
*/
static void* tsip_header_CSeq_destroy(void *self)
{
	tsip_header_CSeq_t *CSeq = self;
	if(CSeq)
	{
		TSK_FREE(CSeq->method);
	}
	else TSK_DEBUG_ERROR("Null CSeq header.");

	return self;
}

static const tsk_object_def_t tsip_header_CSeq_def_s = 
{
	sizeof(tsip_header_CSeq_t),
	tsip_header_CSeq_create,
	tsip_header_CSeq_destroy,
	0
};
const void *tsip_header_CSeq_def_t = &tsip_header_CSeq_def_s;