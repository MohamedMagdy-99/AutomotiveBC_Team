/*****************************************************************************
* Module: OS Module
* File Name: OS.c
* Description: Source file for OS Module
* Author: Mohamed Magdy
* Date: 28-Aug-2021
******************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "OS.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
/* array of that saves the tasks data when created */
strTasksCreationData_t Tasks[MAX_NUM_TASKS];

/* array to save tasks Ids so we can get the task array index */
TaskId_t Tasks_Ids[MAX_NUM_TASKS];

/* array to save tasks priors so we can get the task array index */
TaskPriority_t Tasks_Priority[MAX_NUM_TASKS];

/* variable to save and update sys ticks */
OS_SysTicks_t Sys_CurrentTime = Initial_Value;

/* variable to hold the number of created tasks */
CreatedTasksCount_t CreatedTasksCount = Initial_Value;

/* a flag to indicate a sys tick has occurred */
OS_NewTickFlag_t OS_NewTickFlag = TRUE;

/* a flag to indicate that a task will run */
OS_TaskWillRunFlag_t OS_TaskWillRunFlag = FALSE;

/* a flag to indicate that a task is running */
OS_TaskIsRunningFlag_t OS_TaskIsRunningFlag = FALSE;

/* variable to hold tasks current state */
TaskState_t TasksCurrentState[MAX_NUM_TASKS];

/* currently running taks index */
TaskIndex_t CurrentlyRunningTaskIndex = Initial_Value;

/* OS is initialized flag */
OS_InitializedFlag_t OS_InitializedFlag = FALSE;

/* current cpu load */
OS_CpuLoad_t CurrentCpuLoad;

/* cpu load repetition cycles */
OS_CpuLoad_t CpuLoadCycle = Initial_Value;

/* array to store cpu loads to get average later */
OS_CpuLoad_t CpuLoadBuffer[CPU_LOAD_CALC_CYCLES];

/* OS idle task duration */
OS_IdleTaskDuration_t OS_IdleTaskDuration;

/*- STATIC FUNCTION DECLARATIONS
--------------------------------*/
/* scheduler start */
STATIC Std_ReturnType OS_Scheduler(void);
/* check if any task is currently ready */
STATIC boolean OS_checkIfTaskReady(void);
/* set tasks' index */
STATIC Std_ReturnType OS_setTaskState(TaskId_t Id, TaskState_t TaskState);
/* ticks update callback */
STATIC void OS_CallBack(void);
/* get task's index in array using id */
STATIC Std_ReturnType OS_GetTaskIndex_Id(TaskId_t Id, TaskIndex_t* TaskIndex);
/* calcualtes cpu load average */
STATIC Std_ReturnType OS_CalcCpuLoadAvg(void);
/* cpu load handler */
STATIC Std_ReturnType OS_CpuLoadHandler(void);
/* OS idle task */
STATIC Std_ReturnType OS_IdleTask(void);

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: starts the OS
******************************************************************************************/
Std_ReturnType OS_Start(void)
{
	OS_Scheduler();
	
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: initializes the OS
******************************************************************************************/
Std_ReturnType OS_Init(void)
{
	if(OS_InitializedFlag == TRUE)
	{
		return E_NOT_OK;
	}
	else
	{
		/* initialize tasks states to suspended until they are created */
		uint8_t u8_loopCounter = Initial_Value;
		
		for(u8_loopCounter = Initial_Value; u8_loopCounter < MAX_NUM_TASKS; u8_loopCounter++)
		{
			TasksCurrentState[u8_loopCounter] = SUSPENDED;
		}
		
		/* activate global interrupts */
		EnableGlobalInterrupts();

		/* start timer for first time */
		GptStart_aSync(TIMER_ID, OS_BASE_SYSTICKS_TIMERTICKS, OS_CallBack);	
		
		/* set init flag */
		OS_InitializedFlag = TRUE;
	}

	
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: starts the OS scheduler
******************************************************************************************/
STATIC Std_ReturnType OS_Scheduler(void)
{
	while(TRUE)
	{

		if(OS_NewTickFlag == TRUE)
		{
			/* check for cpu load and handle its calculation */
			OS_CpuLoadHandler();
			
			/* if a task is already running now, leave the if condition */
			if(OS_TaskIsRunningFlag == TRUE)
			{
				/* a task is already running we have to wait */
				/* reset tick flag */
				OS_NewTickFlag = FALSE;
			}
			else
			{
				OS_TaskWillRunFlag = OS_checkIfTaskReady();
				/* if any task is ready to run */
				if(OS_TaskWillRunFlag == TRUE)
				{
					/* compare the priority of ready tasks */
					uint8_t u8_loopCounter = Initial_Value;
					uint8_t maxPrioirtyTemp = MAX_PRIOIRTY;
					for(u8_loopCounter = Initial_Value; u8_loopCounter < CreatedTasksCount; u8_loopCounter++)
					{
						if(TasksCurrentState[u8_loopCounter] == READY)
						{
							if(Tasks_Priority[u8_loopCounter] <= maxPrioirtyTemp)
							{
								/* update new max prio */
								maxPrioirtyTemp = Tasks_Priority[u8_loopCounter];
								/* update current task index to be running */
								CurrentlyRunningTaskIndex = u8_loopCounter;
							}
						}
					}
					/* task is running flag set */
					OS_TaskIsRunningFlag = TRUE;
					/* set state of winner task to running */
					OS_setTaskState(Tasks_Ids[CurrentlyRunningTaskIndex], RUNNING);
					/* run the winner task */
					Tasks[CurrentlyRunningTaskIndex].TaskPointer(Tasks[CurrentlyRunningTaskIndex].Parameters);
					/* block the task that finished task */
					OS_setTaskState(Tasks_Ids[CurrentlyRunningTaskIndex], BLOCKED);
					/* reset tick flag */
					OS_NewTickFlag = FALSE;		
					/* reset task is running flag */
					OS_TaskIsRunningFlag = FALSE;			
				}
				else
				{
					/* reset tick flag */
					OS_NewTickFlag = FALSE;
					
					/* no task needs to run in this ticks, system is idle */
					OS_IdleTask();
				}		
			}

		}
	}
	return E_OK;
}
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: call back function to update OS SysTicks each ISR
******************************************************************************************/
STATIC void OS_CallBack(void)
{
	/* update sys tick */
	Sys_CurrentTime++;
	
	/* update new tick flag */
	OS_NewTickFlag = TRUE;
	
	/* update state of tasks */
	/* compare current sys ticks with tasks periodicity to know which tasks can run now and make them ready */
	uint8_t u8_loopCounter = Initial_Value;
	for(u8_loopCounter = Initial_Value; u8_loopCounter < CreatedTasksCount; u8_loopCounter++)
	{
		if(((Sys_CurrentTime % (Tasks[u8_loopCounter].Periodicity)) == 0) && TasksCurrentState[u8_loopCounter] != SUSPENDED)
		{
			/* set its state to ready */
			OS_setTaskState(Tasks_Ids[u8_loopCounter], READY);
		}
	}		

	/* restart the timer */
	GptStart_aSync(TIMER_ID, OS_BASE_SYSTICKS_TIMERTICKS, OS_CallBack);
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: creates a Task to be added to the system queue.
******************************************************************************************/
Std_ReturnType OS_TaskCreate(TaskId_t* Id, TaskPriority_t Priority, TaskPeriodicityTicks_t Periodicity,
							 ptrTask_t TaskPointer, TaskParameters_t Parameters)
{

	STATIC TaskIndex_t TaskToBeStoredIndex = Initial_Value;

	/* check if new task exceeds the max tasks allowed */
	if(CreatedTasksCount >= MAX_NUM_TASKS)
	{
		return E_NOT_OK;
	}
	/* store task data in array */
	Tasks[TaskToBeStoredIndex].Parameters = Parameters;
	Tasks[TaskToBeStoredIndex].Periodicity = Periodicity;
	Tasks[TaskToBeStoredIndex].TaskPointer = TaskPointer;
	/* set initial state */
	TasksCurrentState[TaskToBeStoredIndex] = READY;
	/* store task index using its id */
	Tasks_Ids[TaskToBeStoredIndex] = TaskToBeStoredIndex;
	/* return the id to user */
	*Id = TaskToBeStoredIndex;
	/* store task index using its prio */
	Tasks_Priority[TaskToBeStoredIndex] = Priority;
	/* increment index and tasks count */
	TaskToBeStoredIndex++;
	CreatedTasksCount++;
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: gets index of task in the tasks' array using its Id
******************************************************************************************/
STATIC Std_ReturnType OS_GetTaskIndex_Id(TaskId_t Id, TaskIndex_t* TaskIndex)
{
		
	uint8_t u8_loopCounter = Initial_Value;
	
	for(u8_loopCounter = Initial_Value; u8_loopCounter < CreatedTasksCount; u8_loopCounter++)
	{
		if(Tasks_Ids[u8_loopCounter] == Id)
		{
			*TaskIndex =  u8_loopCounter;
			return E_OK;
		}
	}
	/* task id not found */
	*TaskIndex = 0xFF;
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: suspends a certain task from being scheduled
******************************************************************************************/
Std_ReturnType OS_TaskSuspend(TaskId_t Id)
{
		TaskIndex_t TaskIndex = Initial_Value;
		/* get the task's index */
		OS_GetTaskIndex_Id(Id, &TaskIndex);
		/* change the state */
		TasksCurrentState[TaskIndex] = SUSPENDED;	
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: calculate CPU load
******************************************************************************************/
STATIC Std_ReturnType OS_calculateCpuLoad(OS_CpuLoad_t* tempCpuLoad)
{
	*tempCpuLoad =  100 - ((OS_IdleTaskDuration*100)/CPU_LOAD_FRAME); 
	return E_OK;
}


/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: task to be executed when system is idle (no other tasks executing)
******************************************************************************************/
STATIC Std_ReturnType OS_IdleTask(void)
{

	OS_IdleTaskDuration++;

	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: unlocks a certain task from being scheduled
******************************************************************************************/
Std_ReturnType OS_TaskResume(TaskId_t Id)
{
	TaskIndex_t TaskIndex = Initial_Value;
	/* get the task's index */
	OS_GetTaskIndex_Id(Id, &TaskIndex);
	/* change the state */
	TasksCurrentState[TaskIndex] = BLOCKED;	
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: changes a certain task's priority
******************************************************************************************/
Std_ReturnType OS_SetPriority(TaskId_t Id, TaskPriority_t Priority)
{
	TaskIndex_t TaskIndex = Initial_Value;
	/* get the task's index */
	OS_GetTaskIndex_Id(Id, &TaskIndex);
	/* change the Priority */
	Tasks[TaskIndex].Periodicity = Priority;	
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: changes a certain task's periodicity
******************************************************************************************/
Std_ReturnType OS_SetPeriodicity(TaskId_t Id, TaskPeriodicityTicks_t Periodicity)
{
	TaskIndex_t TaskIndex = Initial_Value;
	/* get the task's index */
	OS_GetTaskIndex_Id(Id, &TaskIndex);
	/* change the periodicity */
	Tasks[TaskIndex].Periodicity = Periodicity;
	
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: checks is any task is running
******************************************************************************************/
boolean OS_checkIfTaskRunning(void)
{
	return OS_TaskIsRunningFlag;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: checks is any task is ready
******************************************************************************************/
STATIC boolean OS_checkIfTaskReady(void)
{
	uint8_t u8_loopCounter = Initial_Value;
	for(u8_loopCounter = Initial_Value; u8_loopCounter < CreatedTasksCount; u8_loopCounter++)
	{
		if(TasksCurrentState[u8_loopCounter] == READY)
		{
			return TRUE;
		}
	}
	return FALSE;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: changes a task's state or all tasks
******************************************************************************************/
STATIC Std_ReturnType OS_setTaskState(TaskId_t Id, TaskState_t TaskState)
{
	
	uint8_t u8_loopCounter = Initial_Value;
	
	
	if(Id == ALL_TASKS)
	{
		for(u8_loopCounter = Initial_Value; u8_loopCounter < MAX_NUM_TASKS; u8_loopCounter++)
		{
			/* check if a task is suspended don't change it */
			if(TasksCurrentState[u8_loopCounter] == SUSPENDED)
			{
				/* ignore */
				return E_NOT_OK;
			}
			else
			{
				TasksCurrentState[u8_loopCounter] = TaskState;
			}
			
		}	
	}
	else
	{
		/* check if a task is suspended ignore the call */
		if(TasksCurrentState[u8_loopCounter] == SUSPENDED)
		{
			/* ignore */
			return E_NOT_OK;
		}
		else
		{
			TaskIndex_t TaskIndex = Initial_Value;
			/* get the task's index */
			OS_GetTaskIndex_Id(Id, &TaskIndex);
			/* change the state */
			TasksCurrentState[TaskIndex] = TaskState;
		}

	}

	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: gets the current system tick
******************************************************************************************/
Std_ReturnType OS_getCurrentSysTick(OS_SysTicks_t* Sys_CurrentTick)
{
	*Sys_CurrentTick = Sys_CurrentTime;
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: calculates cpu load average
******************************************************************************************/
STATIC Std_ReturnType OS_CalcCpuLoadAvg(void)
{
	/* take the average of all calculated cpu loads */
	uint8_t u8_loopCounter = Initial_Value;
	OS_CpuLoad_t tempCurrentCpuLoad = Initial_Value;
	for(u8_loopCounter = Initial_Value; u8_loopCounter < CPU_LOAD_CALC_CYCLES; u8_loopCounter++)
	{
		tempCurrentCpuLoad += CpuLoadBuffer[u8_loopCounter];
	}
	CurrentCpuLoad = (tempCurrentCpuLoad / CPU_LOAD_CALC_CYCLES);
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: cpu load handling
******************************************************************************************/
STATIC Std_ReturnType OS_CpuLoadHandler(void)
{
	if((Sys_CurrentTime % (CPU_LOAD_FRAME)) == 0 && Sys_CurrentTime != 0)
	{
		/* calculate cpu load according to idle task duration within the past CPU_LOAD_FRAME */
		OS_CpuLoad_t tempCpuLoad;
		OS_calculateCpuLoad(&tempCpuLoad);
		/* save the load */
		CpuLoadBuffer[CpuLoadCycle] = tempCpuLoad;
		/* increment CPU_LOAD_CALC_CYCLES monitor variable */
		CpuLoadCycle++;
		/* reset idle task duration */
		OS_IdleTaskDuration = Initial_Value;
		/* check if we calculated CPU load CPU_LOAD_CALC_CYCLES times already */
		if(CpuLoadCycle == CPU_LOAD_CALC_CYCLES)
		{
			/* calculate cpu load average and store in current cpu load*/
			OS_CalcCpuLoadAvg();
			
			/* reset the cpu load cycle */
			CpuLoadCycle = Initial_Value;
		}
	}
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: fun to get current CPU load
******************************************************************************************/
Std_ReturnType OS_getCpuLoad(OS_CpuLoad_t* CpuLoad)
{
	*CpuLoad = CurrentCpuLoad;
	return E_OK;
}



