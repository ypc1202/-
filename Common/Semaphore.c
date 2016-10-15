#include <rtx51tny.h>                 /* RTX-51 tiny functions & defines      */
#include "Common.h"
#include "Semaphore.h"

SEM_SET sem_tab[MAX_SEMAPHORES] = {0};

/* init semaphore */
#pragma disable
void init_semaphore(uint8_t sem_id, uint8_t max_count, uint8_t count)
{
    sem_tab[sem_id].max_count = max_count;
    sem_tab[sem_id].count = count;
    sem_tab[sem_id].pending_tasks = 0;
}

/* wait semaphore */
#pragma disable
char pend_sem(uint8_t sem_id)
{
    if(sem_tab[sem_id].count > 0) 
    {
        sem_tab[sem_id].count--;      /* get semaphore */
        return SEM_FAIL;
    }
        
    /* mark for waiting semaphore */
    sem_tab[sem_id].pending_tasks = (1 << os_running_task_id()); 
    
    return SEM_OK;
}

void pend_semaphore(uint8_t sem_id)
{
    if(pend_sem(sem_id) == 0)
    {
        while(os_wait(K_TMO, 255, 0) != RDY_EVENT);    /* waiting until the task is ready */
    }
}

/* release semaphore */
#pragma disable
char release_sem(uint8_t sem_id)
{
    uint8_t  i = 0;
    uint16_t temp = 1;
    
    if((sem_tab[sem_id].count > 0)||(sem_tab[sem_id].pending_tasks == 0))
    {
        sem_tab[sem_id].count++; /* release semaphore */
            
        if(sem_tab[sem_id].count > sem_tab[sem_id].max_count)
        {
            sem_tab[sem_id].count = sem_tab[sem_id].max_count;
        }
                
        return SEM_FAIL;
    }
        
    for(i = 0; i < MAX_TASK; i++)
    {
        if(((sem_tab[sem_id].pending_tasks) & (temp)) != 0)
        {
            /* look out for tasklist*/
            if(((sem_tab[sem_id].pending_tasks) & (~(1<<i))) != 0)
            {                            
                return (i);                                     /* return the task id waiting semaphore*/
            }
        }
        temp <<= 1;
    }
        
    return SEM_OK;
}

void release_semaphore(uint8_t sem_id) 
{
    char task_id = 0;
    
    task_id = release_sem(sem_id);
    
    if(task_id != SEM_FAIL)
    {
        os_set_ready(task_id);  /* task id is ready */
        os_switch_task();
    }
}