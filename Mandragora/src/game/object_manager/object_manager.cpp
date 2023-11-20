#include "pch.h"
#include "object_manager.h"

game::player* object_manager::get_local_player() 
{
    return *(game::player**)(globals::executable_base + offsets::p_local_player);
}