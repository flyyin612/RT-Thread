#ifndef __RT_DEF_H__
#define __RT_DEF_H__

#include <rtconfig.h>

/*
*********************************************************************************
*																	数据类型
*********************************************************************************
*/
/*RT-Thread basic data type definitions */
typedef signed char									rt_int8_t;
typedef signed short								rt_int16_t;
typedef signed long									rt_int32_t;
typedef unsigned char								rt_uint8_t;
typedef unsigned short							rt_uint16_t;
typedef unsigned long								rt_uint32_t;
typedef int													rt_bool_t;
	
/*32bit CPU*/
typedef long												rt_base_t;
typedef unsigned long								rt_ubase_t;

typedef rt_base_t										rt_err_t;
typedef rt_uint32_t									rt_time_t;
typedef rt_uint32_t									rt_tick_t;
typedef rt_base_t 									rt_flag_t;
typedef rt_ubase_t 									rt_size_t;
typedef rt_ubase_t 									rt_dev_t;
typedef rt_base_t 									rt_off_t;

/*boolean type definitions*/
#define RT_TRUE											1
#define RT_FALSE										0

#ifdef __CC_ARM 
	#define	rt_inline									static __inline
	#define ALIGN(n)									__attribute__((aligned(n)))
	
#elif	define (__IAR_SYSTEMS_ICC__)
	#define	rt_inline 								static inline 
	#define ALIGN(n)									PRAGMA(data_alignment=n)

#elif	define(__GNUC__)
	#define rt_inline 								static inline 
	#define ALIGN(n)									__attribute__((aligned(n)))
#else
	#error	not supported tool chain
#endif
	
#define RT_ALIGN(size,align)				(((size) + (align) - 1) & ~((align) - 1))
#define RT_ALIGN_DOWN(size,align)   ((size) & ~((align) - 1))
	
#define RT_NULL											(0)
	
/*
***************************************************************************************
*																			错误码定义
***************************************************************************************
*/
/* RT-Thread 错误码重定义 */
#define RT_EOK														0
#define RT_ERROR													1
#define RT_ETIMEOUT												2
#define RT_EFULL													3
#define RT_EEMPTY													4
#define RT_ENOMEM													5
#define RT_ENOSYS													6
#define RT_EBUSY													7
#define RT_EIO														8
#define RT_EINTR													9
#define RT_EINVAL													10

/*
****************************************************************************************
*																			双向链表结构体
****************************************************************************************
*/
struct rt_list_node
{
	struct rt_list_node *next;								/*指向后一个节点*/
	struct rt_list_node *prev;								/*指向前一个节点*/
};
typedef struct rt_list_node rt_list_t;

/*
 *****************************************************************************************
 *																	内核对象结构体
 *****************************************************************************************
*/
/**
	*内核对象基础数据结构
  */
struct rt_object
{
	char 					name[RT_NAME_MAX];										/*内核对象的名字*/
	rt_uint8_t    type;																	/*内核对象的类型*/
	rt_uint8_t		flag;																	/*内核对象的状态*/
	
	rt_list_t 		list;																	/*内核对象的列表节点*/
};
typedef struct rt_object *rt_object_t;								/*内核对象数据类型重定义*/

/**
	*对象类型由下面的宏来使能，这些宏通常在rtconfig.h中定义
	* - Thread
	* - Semaphore
	* - Mutex
	* - Event
	* - MailBox
	* - MessageQueue
	* - MemHeap
	* - MemPool
	*	- Device
	*	-	Timer
	*	-	Module
	*	-	Unknown
	*	-	Static
	*/
enum rt_object_class_type
{
	RT_Object_Class_Thread = 0,								/*对象是线程*/
	RT_Object_Class_Semaphore,								/*对象是信号量*/
	RT_Object_Class_Mutex,										/*对象是互斥量*/
	RT_Object_Class_Event,										/*对象是事件*/
	RT_Object_Class_MailBox,									/*对象是邮箱*/
	RT_Object_Class_MessageQueue,							/*对象是消息队列*/
	RT_Object_Class_MemHeap,									/*对象是内存堆*/
	RT_Object_Class_MemPool,									/*对象是内存池*/
	RT_Object_Class_Device,										/*对象是设备*/
	RT_Object_Class_Timer,										/*对象是定时器*/
	RT_Object_Class_Module,										/*对象是模块*/
	RT_Object_Class_Unknown,									/*对象未知*/
	RT_Object_Class_Static = 0x80							/*对象是静态对象*/
};

/**
	*内核对象信息结构体
	*/
struct rt_object_information
{
	enum	rt_object_class_type type;					/*对象类型*/
	rt_list_t 								 object_list;		/*对象列表节点*/
	rt_size_t 								 object_size;		/*对象大小*/
};

/*
*******************************************************************************************
*																			线程结构体
*******************************************************************************************
*/
struct rt_thread
{
	/* rt 对象 */
	char        name[RT_NAME_MAX];    /* 对象的名字 */
	rt_uint8_t  type;                 /* 对象类型 */
	rt_uint8_t  flags;                /* 对象的状态 */
	rt_list_t   list;                 /* 对象的列表节点 */
	
	rt_list_t 		tlist;				/*线程链表节点*/
	
	void 					*sp;					/*线程栈指针*/
	void          *entry;				/*线程入口地址*/
	void          *parameter;		/*线程形参*/
	void          *stack_addr;	/*线程起始地址*/
	rt_uint32_t   stack_size;		/*线程栈大小，单位为字节*/	
	
	rt_ubase_t 		remaining_tick;		/*用于实现阻塞延时*/
};
typedef struct rt_thread *rt_thread_t;

#endif

