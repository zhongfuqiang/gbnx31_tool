/*******************************************************************************
	File name: 		NxRulerTypes.h
	Author: 		李明
	Version:  		1.0
	Date:    		2013年5月13日
	Description: 	Nxruler QGW 376.1 类型定义头文件
	                               
	Others:       
    Function List: 
    1. History: 
                    
          1)  Date:
          2)  Author:
          3)  Modification:  Created
    2. ...
*******************************************************************************/
#if !defined(_NX_RULER_TYPES_H_)
#define _NX_RULER_TYPES_H_

#pragma pack(push)  // 采用一字节对齐
#pragma pack(1)
#if 0
typedef unsigned char  UINT8;
typedef unsigned short UINT16;



// 协议相关宏定义
#define MT_PN_MAX    (2033)
#define MT_SEQ2CS_BYTES_MAX    (16384)             // 每单帧允许SEQ与CS之间数据字节数最大值
// 封解帧部分字长
#define MT_CA_LEN                 (8)                // 控制域与地址域总字长 
#define MT_CANS_LEN               (8)               // 控制域C 地址域A AFN SEQ字节总长
#define MT_UN_USER_LEN            (6)                // 报文中非数据域总长度  0x68 0x68 L L CS 0x16
#define MT_DADT_LEN               (4)                // 数据标识字长 DaDt  
#define MT_AFN_LEN                (1)                // AFN 字长
#define MT_DADT_ERR_LEN           (MT_DADT_LEN + 1)  // DaDt 与 ERR总字长


#define MT_TM_ADDR_MAX            (65535)            // 终端地址的最大值
#define MT_TM_ADDR_MIN            (1)                // 终端地址的最小值

#define MT_CTRL_DIR_M2T           (0x80)             // 控制码 传输方向 主站到终端(下行)
#define MT_CTRL_DIR_T2M           (0x7F)             // 控制码 传输方向 终端到主到(上行)

#define MT_CTRL_PRM_MASTR         (0x40)             // 控制码 启动标志 主动站
#define MT_CTRL_PRM_SLAVE         (0xBF)             // 控制码 启动标志 从动站

#define MT_CTRL_FCB_ENABLE        (0x20)             // 帧计数位 
#define MT_CTRL_FCV_ENABLE        (0x10)             // 帧计数位有效位,为1时 FCB 有效

#define MT_CTRL_ACD_EVENT_HAVE    (0x20)             // 请求访问位 为 1 终端有事件需要上报
#define MT_CTRL_ACD_EVENT_NONE    (0xDF)             // 请求访问位 为 0 终端无事件需要上报

// bit set 
#define MT_BSET_SEQ_TPV           (0x80)             // bit set seq tpv 字段
#define MT_BSET_SEQ_FIR           (0x40)             // bit set seq fir 字段
#define MT_BSET_SEQ_FIN           (0x20)             // bit set seq fin 字段
#define MT_BSET_SEQ_CON           (0x10)             // bit set seq con 字段

#define   MT_SEND_LEN_MAX   (10240)                  // 一个报文buffer的最大长度

#define MT_DA_PN_MAX            (2040)               // DA Pn 最大值 
#define MT_DA_PN_MIN            (0)                  // Da Pn 最小值
#define MT_DT_FN_MAX            (248)                // Dt Fn 最大值
#define MT_DT_FN_MIN            (1)                  // Dt Fn 最小值
#define MT_PW_LEN               (16)                 // 消息认证长度
#define MT_PACK_LEN_MIN         (18)                 // 消息的最小长度
#define MT_PACK_LEN_MAX         (16384)               // 消息最大长度，目前暂定2048
#define MT_MST_ADDR_MAX         (127)                // 主站地址最大值
// 376.1 规约命令字
// 组织规则 AFN_XX_FN_X  各占一个字节   AFN 高8位， FN 低8位

typedef enum
{
    CMD_AFN_0_FN_0_UNKOWN,                         // 未知命令     

    /* (0)确认∕否认（AFN=00H） */
    CMD_AFN_0_FN_1_ALL_OK          = 0x0001,       // 全部确认
    CMD_AFN_0_FN_2_ALL_DENY        = 0x0002,       // 全部否认
    CMD_AFN_0_FN_3_ONE_BY_ONE      = 0x0003,       // 按数据单元标识确认和否认
    // F4 - F248 备用

    /* (1)复位命令（AFN=01H） */
    CMD_AFN_1_FN_1_HARD_INIT       = 0x0101,       // 硬件初始化
    CMD_AFN_1_FN_2_DATA_INIT       = 0x0102,       // 数据区初始化
    CMD_AFN_1_FN_3_FACTORY_RESET   = 0x0103,       // 参数及全体数据区初始化（即恢复至出厂配置）
    CMD_AFN_1_FN_4_PARA_INIT       = 0x0104,       // 参数（除与系统主站通信有关的）及全体数据区初始化
    // F5 - F248 备用

    /* (2) 链路接口检测（AFN=02H） */
    CMD_AFN_2_FN_1_LOG_IN          = 0x0201,       // 登录
    CMD_AFN_2_FN_2_LOG_OUT         = 0x0202,       // 退出登录
    CMD_AFN_2_FN_3_HEART_BEAT      = 0x0203,       // 心跳
    // F4 - F248 备用

    /* (4) 设置参数（AFN == 04H） */
    CMD_AFN_4_FN_1_CON_UP_CFG       = 0x0401,       // 集中器上行通信口通信参数设置
    //CMD_AFN_4_FN_2_CON_UP_WAY_ETH   = 0x0402,       // 集中器上行通信工作方式（以太专网或虚拟专网） 
	CMD_AFN_4_FN_2_CON_UP_REWORD    = 0x4002,       // 集中器上行通信口中继转发配置
    CMD_AFN_4_FN_3_MST_IP_PORT      = 0x0403,       // 主站IP地址和端口
    CMD_AFN_4_FN_4_PHONE_MST_SMS    = 0x0404,       // 主站电话号码和短信中心号码
    CMD_AFN_4_FN_5_CON_UP_PARA      = 0x0405,       // 集中器上行通信消息认证参数设置
    CMD_AFN_4_FN_6_TEAM_ADDR        = 0x0406,       // 集中器组地址设置
    CMD_AFN_4_FN_7_CON_IP_PORT      = 0x0407,       // 集中器IP地址和端口
    CMD_AFN_4_FN_8_CON_UP_WAY       = 0x0408,       // 集中器上行通信工作方式
    CMD_AFN_4_FN_9_CFG_TML_MNT      = 0x0409,       // 集中器与终端通信读取数据运行参数设置
    CMD_AFN_4_FN_10_CON_DOWN_CFG    = 0x040A,       // 集中器下行通信模块的参数设置
    CMD_AFN_4_FN_11_VPN_PWD         = 0x040B,       // 虚拟专网用户名、密码
    CMD_AFN_4_FN_12_CON_UP_LIMIT    = 0x040C,       // 集中器上行通信流量门限设置
    CMD_AFN_4_FN_13_CON_CASC_CFG    = 0x040D,       // 集中器级联通信参数
    CMD_AFN_4_FN_17_CFG_EVENT       = 0x0411,       // 集中器事件记录配置设置
    CMD_AFN_4_FN_18_CFG_TM_STATE    = 0x0412,       // 集中器状态量输入参数
    CMD_AFN_4_FN_19_CFG_METERING    = 0x0413,       // 计量表基本配置基本参数
    CMD_AFN_4_FN_25_POWER_LIMIT     = 0x0419,       // 电能量限值参数
    CMD_AFN_4_FN_26_FACTOR_LIMIT    = 0x041A,       // 测量点功率因数分段限值
    CMD_AFN_4_FN_28_CFG_POWER       = 0x041C,       // 电能类数据配置参数
    CMD_AFN_4_FN_29_CFG_UN_POWER    = 0x041D,       // 非电量数据配置参数
    //CMD_AFN_4_FN_33_TIMING_REPORT_1 = 0x0421,       // 定时上报1类数据任务设置
	CMD_AFN_4_FN_33_CFG_NOT_ELEC	  = 0x0421,       // 非电气测量点数据参数配置
    CMD_AFN_4_FN_34_TIMING_REPORT_2 = 0x0422,       // 定时上报2类数据任务设置
    CMD_AFN_4_FN_35_STOP_TIMING_REPORT_1   = 0x0423,// 定时上报1类数据任务启动/停止设置
    CMD_AFN_4_FN_36_STOP_TIMING_REPORT_2   = 0x0424,// 定时上报2类数据任务启动/停止设置
    CMD_AFN_4_FN_41_CFG_TML_MNT       = 0x0429,     // 终端配置基本参数设置
    CMD_AFN_4_FN_42_CFG_TML_STATE     = 0x042A,     // 终端状态量输入参数
    CMD_AFN_4_FN_43_CFG_TML_TRANS     = 0x042B,     // 终端透传设备配置


    /* (5) 控制命令（AFN=05H） */
    CMD_AFN_5_FN_1_REMOTE_SWITCH_OFF = 0x0501,       // 遥控跳闸
    CMD_AFN_5_FN_2_PERMIT_SWITCH_ON  = 0x0502,       // 允许合闸
    CMD_AFN_5_FN_29_STRT_AUTO_REPORT = 0x051D,       // 允许集中器主动上报
    CMD_AFN_5_FN_31_TIME_TICK        = 0x051F,       // 对时命令
    CMD_AFN_5_FN_37_STOP_AUTO_REPORT = 0x0525,       // 禁止集中器主动上报
    CMD_AFN_5_FN_38_LINK_MST_TML     = 0x0526,       // 激活集中器连接主站
    CMD_AFN_5_FN_39_UNLINK_MST_TML   = 0x0527,       // 命令集中器断开连接
    CMD_AFN_5_FN_49_PORT_TML_SUSPEND = 0x0531,       // 命令指定通信端口暂停与终端通信读取数据
    CMD_AFN_5_FN_50_PORT_TML_RESUME  = 0x0532,       // 命令指定通信端口恢复与终端通信读取数据
    CMD_AFN_5_FN_51_PORT_TML_AGAIN   = 0x0533,       // 命令指定通信端口重新与终端通信读取数据
    CMD_AFN_5_FN_52_INIT_ROUT_INFO   = 0x0534,       // 初始化指定通信端口下的全部中继路由信息
    CMD_AFN_5_FN_53_DEL_ALL_TML      = 0x0535,       // 删除指定通信端口下的全部终端
    

    /* (6) 身份认证及密钥协商（AFN=06H） */
    CMD_AFN_6_FN_1_ID_AUTH_Q         = 0x0601,       // 身份认证请求
    CMD_AFN_6_FN_2_ID_AUTH_A         = 0x0602,       // 身份认证响应
    CMD_AFN_6_FN_3_RAND_Q            = 0x0603,       // 取随机数请求
    CMD_AFN_6_FN_4_RAND_A            = 0x0604,       // 取随机数响应
 
    /* (9) 请求集中器配置及信息（AFN=09H） */
    CMD_AFN_9_FN_1_CON_VERSION        = 0x0901,       // 集中器版本信息
    CMD_AFN_9_FN_4_SUPPORT_PARA_CFG  = 0x0904,       // 集中器支持的参数配置
    CMD_AFN_9_FN_5_SUPPORT_CTRL_CFG  = 0x0905,       // 集中器支持的控制配置
    CMD_AFN_9_FN_6_SUPPORT_ASK1_CFG  = 0x0906,       // 集中器支持的1类数据配置
    CMD_AFN_9_FN_7_SUPPORT_ASK2_CFG  = 0x0907,       // 集中器支持的2类数据配置
    CMD_AFN_9_FN_8_SUPPORT_EVNT_CFG  = 0x0908,       // 集中器支持的事件记录配置

 

    /* (10)  查询参数（AFN=0AH） */
    CMD_AFN_A_FN_1_CON_UP_CFG        = 0x0A01,       // 集中器上行通信口通信参数设置
    CMD_AFN_A_FN_2_CON_UP_WAY_ETH    = 0x0A02,       // 集中器上行通信工作方式（以太专网或虚拟专网）
    CMD_AFN_A_FN_3_MST_IP_PORT       = 0x0A03,       // 主站IP地址和端口
    CMD_AFN_A_FN_4_PHONE_MST_SMS     = 0x0A04,       // 主站电话号码和短信中心号码
    CMD_AFN_A_FN_5_CON_UP_PARA       = 0x0A05,       // 集中器上行通信消息认证参数设置
    CMD_AFN_A_FN_6_TEAM_ADDR         = 0x0A06,       // 集中器组地址设置
    CMD_AFN_A_FN_7_CON_IP_PORT       = 0x0A07,       // 集中器IP地址和端口
    CMD_AFN_A_FN_8_CON_UP_WAY        = 0x0A08,       // 集中器上行通信工作方式
    CMD_AFN_A_FN_9_CFG_TML_MNT       = 0x0A09,       // 集中器与终端通信读取数据运行参数设置
    CMD_AFN_A_FN_10_CON_DOWN_CFG     = 0x0A0A,       // 集中器下行通信模块的参数设置
    CMD_AFN_A_FN_11_VPN_PWD          = 0x0A0B,       // 虚拟专网用户名、密码
    CMD_AFN_A_FN_12_CON_UP_LIMIT     = 0x0A0C,       // 集中器上行通信流量门限设置
    CMD_AFN_A_FN_13_CON_CASC_CFG     = 0x0A0D,       // 集中器级联通信参数
    CMD_AFN_A_FN_17_CFG_EVENT       = 0x0A11,       // 集中器事件记录配置设置
    CMD_AFN_A_FN_18_CFG_TM_STATE    = 0x0A12,       // 集中器状态量输入参数
    CMD_AFN_A_FN_19_CFG_METERING    = 0x0A13,       // 计量表基本配置基本参数
    CMD_AFN_A_FN_25_POWER_LIMIT     = 0x0A19,       // 电能量限值参数
    CMD_AFN_A_FN_26_FACTOR_LIMIT    = 0x0A1A,       // 测量点功率因数分段限值
    CMD_AFN_A_FN_28_CFG_POWER       = 0x0A1C,       // 电能类数据配置参数
    CMD_AFN_A_FN_29_CFG_UN_POWER    = 0x0A1D,       // 非电量数据配置参数
    CMD_AFN_A_FN_33_TIMING_REPORT_1 = 0x0A21,       // 定时上报1类数据任务设置
    CMD_AFN_A_FN_34_TIMING_REPORT_2 = 0x0A22,       // 定时上报2类数据任务设置
    CMD_AFN_A_FN_35_STOP_TIMING_REPORT_1     = 0x0A23,       // 定时上报1类数据任务启动/停止设置
    CMD_AFN_A_FN_36_STOP_TIMING_REPORT_2     = 0x0A24,       // 定时上报2类数据任务启动/停止设置
    CMD_AFN_A_FN_41_CFG_TML_MNT        = 0x0A09,       // 终端配置基本参数设置
    CMD_AFN_A_FN_42_CFG_TML_STATE      = 0x0A09,       // 终端状态量输入参数
    CMD_AFN_A_FN_43_CFG_TML_TRANS      = 0x0A09,       // 终端透传设备配置

    /* (11) 请求任务数据（AFN=0BH） */
    CMD_AFN_B_FN_1_TIMING_REPORT_1    = 0x0B01,       // 请求定时上报1类数据任务
    CMD_AFN_B_FN_2_TIMING_REPORT_2    = 0x0B02,       // 请求定时上报2类数据任务

    /* (12) 请求1类数据（AFN=0CH） */
    CMD_AFN_C_FN_1_CON_CALENDAR_CLOCK  = 0x0C01,       // 集中器日历时钟
    CMD_AFN_C_FN_2_CON_PARA_STATE      = 0x0C02,       // 集中器参数状态
    CMD_AFN_C_FN_3_CON_UPCOM_STATE     = 0x0C03,       // 集中器上行通信状态
    CMD_AFN_C_FN_4_CON_EC_VALUE        = 0x0C04,       // 集中器事件计数器当前值
    CMD_AFN_C_FN_5_CON_EVNT_FLAG       = 0x0C05,       // 集中器事件标志状态
    CMD_AFN_C_FN_6_CON_STATE_BIT       = 0x0C06,       // 集中器状态量及变位标志
    CMD_AFN_C_FN_7_CON_MONTH_FLOW      = 0x0C07,       // 集中器与主站当日、月通信流量
    CMD_AFN_C_FN_9_CURENT_ELEC         = 0x0C09,       // 当前三相及总有/无功功率、功率因数，三相电压、电流、零序电流、视在功率
    CMD_AFN_C_FN_10_DROP_PHASE         = 0x0C0A,       // A、B、C三相断相统计数据及最近一次断相记录
    CMD_AFN_C_FN_12_POWER_HAVE         = 0x0C0C,       // 当前A、B、C三相正/反向有功功电能示值，组合无功1/2电能示值
    CMD_AFN_C_FN_13_POWER_FORTH        = 0x0C0D,       // 当前正向有/无功电能示值、一/四象限无功电能示值
    CMD_AFN_C_FN_14_POWER_BACK         = 0x0C0E,       // 当前反向有/无功电能示值、二/三象限无功电能示值
    CMD_AFN_C_FN_13_PHASE_ANGLE        = 0x0C0D,       // 当前电压、电流相位角
    CMD_AFN_C_FN_17_CUR_CURVE          = 0x0C11,       // 当前总基波/谐波有功/无功功率
    CMD_AFN_C_FN_18_HARM_VALID         = 0x0C12,       // 当前A、B、C三相电压、电流2～N次谐波有效值
    CMD_AFN_C_FN_19_HARM_ROTIO         = 0x0C13,       // 当前A、B、C三相电压、电流2～N次谐波含有率
    CMD_AFN_C_FN_20_HARM_ROTIO_V       = 0x0C14,       // 当前A、B、C三相电压20~N次谐波含有率
    CMD_AFN_C_FN_21_HARM_ROTIO_E       = 0x0C15,       // 当前A、B、C三相电流20~N次谐波含有率
    
    CMD_AFN_C_FN_22_FLICKER_LONG       = 0x0C16,       // 长闪变
    CMD_AFN_C_FN_23_FLICKER_SHORT      = 0x0C17,       // 短闪变
    CMD_AFN_C_FN_25_DC_REAL_TIME       = 0x0C19,       // 直流模拟实时数据
    CMD_AFN_C_FN_26_UNBALAN_E_V        = 0x0C1A,       // 电压、电流不平衡度
    CMD_AFN_C_FN_27_UNBALAN_FREZ_V     = 0x0C1B,       // 小时冻结电压不平衡度
    CMD_AFN_C_FN_28_UNBALAN_FREZ_E     = 0x0C1C,       // 小时冻结电流不平衡度
    CMD_AFN_C_FN_29_FREZ_NOR_POWER     = 0x0C1D,       // 小时冻结非电量数据
    CMD_AFN_C_FN_33_FREZ_HAVE_POWER    = 0x0C21,       // 小时冻结有功功率
    CMD_AFN_C_FN_34_FREZ_HAVE_POWER_A  = 0x0C22,       // 小时冻结A相有功功率
    CMD_AFN_C_FN_35_FREZ_HAVE_POWER_B  = 0x0C23,       // 小时冻结B相有功功率
    CMD_AFN_C_FN_36_FREZ_HAVE_POWER_C  = 0x0C24,       // 小时冻结C相有功功率
    CMD_AFN_C_FN_37_FREZ_NONE_POWER    = 0x0C25,       // 小时冻结无功功率
    CMD_AFN_C_FN_38_FREZ_NONE_POWER_A  = 0x0C26,       // 小时冻结A相无功功率
    CMD_AFN_C_FN_39_FREZ_NONE_POWER_B  = 0x0C27,       // 小时冻结B相无功功率
    CMD_AFN_C_FN_40_FREZ_NONE_POWER_C  = 0x0C28,       // 小时冻结C相无功功率
    
    CMD_AFN_C_FN_41_FREZ_V_A           = 0x0C29,       // 小时冻结A相电压
    CMD_AFN_C_FN_42_FREZ_V_B           = 0x0C2A,       // 小时冻结B相电压
    CMD_AFN_C_FN_43_FREZ_V_C           = 0x0C2B,       // 小时冻结C相电压
    CMD_AFN_C_FN_44_FREZ_E_A           = 0x0C2C,       // 小时冻结A相电流
    CMD_AFN_C_FN_45_FREZ_E_B           = 0x0C2D,       // 小时冻结B相电流
    CMD_AFN_C_FN_46_FREZ_E_C           = 0x0C2E,       // 小时冻结C相电流
    
    CMD_AFN_C_FN_47_CFG_TML_MNT     = 0x0C2F,       // 小时冻结零序电流
    CMD_AFN_C_FN_49_CFG_TML_MNT     = 0x0C31,       // 小时冻结正向有功总电能示值
    CMD_AFN_C_FN_50_CFG_TML_MNT     = 0x0C32,       // 小时冻结正向无功总电能示值
    CMD_AFN_C_FN_51_CFG_TML_MNT     = 0x0C33,       // 小时冻结反向有功总电能示值
    CMD_AFN_C_FN_52_CFG_TML_MNT     = 0x0C34,       // 小时冻结反向无功总电能示值
    CMD_AFN_C_FN_53_CFG_TML_MNT     = 0x0C35,       // 小时冻结总功率因数
    CMD_AFN_C_FN_54_CFG_TML_MNT     = 0x0C36,       // 小时冻结A相功率因数
    CMD_AFN_C_FN_55_CFG_TML_MNT     = 0x0C37,       // 小时冻结B相功率因数
    CMD_AFN_C_FN_56_CFG_TML_MNT     = 0x0C38,       // 小时冻结C相功率因数
    CMD_AFN_C_FN_57_CFG_TML_MNT     = 0x0C39,       // 终端日历时钟
    CMD_AFN_C_FN_90_NOT_ELEC        = 0x0C5A,       // 取得非电气量
    
    /* (13) 请求2类数据（AFN=0DH） */
    CMD_AFN_D_FN_1_TM_UP_CFG        = 0x0D01,       // 集中器日历时钟
    CMD_AFN_D_FN_2_TM_UP_WAY_ETH    = 0x0D02,       // 集中器参数状态
    CMD_AFN_D_FN_3_MST_IP_PORT      = 0x0D03,       // 集中器上行通信状态
    CMD_AFN_D_FN_4_PHONE_SMS        = 0x0D04,       // 集中器事件计数器当前值
    CMD_AFN_D_FN_5_TM_UP_PARA       = 0x0D05,       // 集中器事件标志状态
    CMD_AFN_D_FN_6_TEAM_ADDR        = 0x0D06,       // 集中器状态量及变位标志
    CMD_AFN_D_FN_7_TML_IP_PORT      = 0x0D07,       // 集中器与主站当日、月通信流量
    CMD_AFN_D_FN_8_TM_UP_WAY        = 0x0D08,       // 当前三相及总有/无功功率、功率因数，三相电压、电流、零序电流、视在功率
    CMD_AFN_D_FN_9_CFG_TML_MNT      = 0x0D09,       // A、B、C三相断相统计数据及最近一次断相记录
    CMD_AFN_D_FN_10_TM_DOWN_CFG     = 0x0D0A,       // 当前A、B、C三相正/反向有功功电能示值，组合无功1/2电能示值
    CMD_AFN_D_FN_11_VPN_PWD         = 0x0D0B,       // 当前正向有/无功电能示值、一/四象限无功电能示值
    CMD_AFN_D_FN_12_TM_UP_LIMIT     = 0x0D0C,       // 当前反向有/无功电能示值、二/三象限无功电能示值
    CMD_AFN_D_FN_13_TM_CASC_CFG     = 0x0D0D,       // 当前电压、电流相位角
    CMD_AFN_D_FN_14_CFG_EVENT       = 0x0D11,       // 当前总基波/谐波有功/无功功率
    CMD_AFN_D_FN_15_CFG_TM_STATE    = 0x0D12,       // 当前A、B、C三相电压、电流2～N次谐波有效值
    CMD_AFN_D_FN_17_CFG_METERING    = 0x0D13,       // 当前A、B、C三相电压、电流2～N次谐波含有率
    CMD_AFN_D_FN_18_POWER_LIMIT     = 0x0D19,       // 当前A、B、C三相电压20~N次谐波含有率
    CMD_AFN_D_FN_19_FACTOR_LIMIT    = 0x0D1A,       // 当前A、B、C三相电流20~N次谐波含有率
    CMD_AFN_D_FN_20_CFG_POWER       = 0x0D1C,       // 长闪变
    CMD_AFN_D_FN_21_CFG_UN_POWER    = 0x0D1D,       // 短闪变
    CMD_AFN_D_FN_22_TIMING_REPORT_1 = 0x0D21,       // 直流模拟实时数据
    CMD_AFN_D_FN_23_TIMING_REPORT_2 = 0x0D22,       // 电压、电流不平衡度
    CMD_AFN_D_FN_25_STOP_TIMING_REPORT_1     = 0x0D23,       // 小时冻结电压不平衡度
    CMD_AFN_D_FN_26_STOP_TIMING_REPORT_2     = 0x0D24,       // 小时冻结电流不平衡度
    CMD_AFN_D_FN_27_CFG_TML_MNT     = 0x0D09,       // 小时冻结非电量数据
    CMD_AFN_D_FN_28_CFG_TML_MNT     = 0x0D09,       // 小时冻结有功功率
    CMD_AFN_D_FN_29_CFG_TML_MNT     = 0x0D09,       // 小时冻结A相有功功率
    CMD_AFN_D_FN_33_CFG_TML_MNT     = 0x0D09,       // 小时冻结B相有功功率
    CMD_AFN_D_FN_34_CFG_TML_MNT     = 0x0D09,       // 小时冻结C相有功功率
    CMD_AFN_D_FN_35_CFG_TML_MNT     = 0x0D09,       // 小时冻结无功功率
    CMD_AFN_D_FN_36_CFG_TML_MNT     = 0x0D09,       // 小时冻结A相无功功率
    CMD_AFN_D_FN_37_CFG_TML_MNT     = 0x0D09,       // 小时冻结B相无功功率
    CMD_AFN_D_FN_38_CFG_TML_MNT     = 0x0D09,       // 小时冻结C相无功功率
    
    CMD_AFN_D_FN_39_CFG_TML_MNT     = 0x0D09,       // 小时冻结A相电压
    CMD_AFN_D_FN_40_CFG_TML_MNT     = 0x0D09,       // 小时冻结B相电压
    CMD_AFN_D_FN_41_CFG_TML_MNT     = 0x0D09,       // 小时冻结C相电压
    CMD_AFN_D_FN_42_CFG_TML_MNT     = 0x0D09,       // 小时冻结A相电流
    CMD_AFN_D_FN_43_CFG_TML_MNT     = 0x0D09,       // 小时冻结B相电流
    CMD_AFN_D_FN_44_CFG_TML_MNT     = 0x0D09,       // 小时冻结C相电流
    
    CMD_AFN_D_FN_45_CFG_TML_MNT     = 0x0D09,       // 小时冻结零序电流
    CMD_AFN_D_FN_46_CFG_TML_MNT     = 0x0D09,       // 小时冻结正向有功总电能示值
    CMD_AFN_D_FN_47_CFG_TML_MNT     = 0x0D09,       // 小时冻结正向无功总电能示值
    CMD_AFN_D_FN_48_CFG_TML_MNT     = 0x0D09,       // 小时冻结反向有功总电能示值
    CMD_AFN_D_FN_52_CFG_TML_MNT     = 0x0D09,       // 小时冻结反向无功总电能示值
    CMD_AFN_D_FN_53_CFG_TML_MNT     = 0x0D09,       // 小时冻结总功率因数
    CMD_AFN_D_FN_54_CFG_TML_MNT     = 0x0D09,       // 小时冻结A相功率因数
    CMD_AFN_D_FN_55_CFG_TML_MNT     = 0x0D09,       // 小时冻结B相功率因数
    CMD_AFN_D_FN_56_CFG_TML_MNT     = 0x0D09,       // 小时冻结C相功率因数
    CMD_AFN_D_FN_57_CFG_TML_MNT     = 0x0D09,       // 终端日历时钟

    /* (14) 请求3类数据（AFN=0EH） */
    CMD_AFN_E_FN_1_EVENT_1          = 0x0E01,       // 请求重要事件
    CMD_AFN_E_FN_2_EVENT_2          = 0x0E02,       // 请求一般事件
	
    /* (15) 文件传输（AFN=0FH） */
     CMD_AFN_F_FN_1_TRANS_WAY       = 0x0E01,       // 文件传输方式1

    /* (16) 数据转发（AFN=10H） */
    CMD_AFN_G_FN_1_CFG_TML_MNT     = 0x1001,       // 透明转发
    CMD_AFN_G_FN_9_CFG_TML_MNT     = 0x1009,       // 转发主站直接对终端的抄读数据命令
    CMD_AFN_G_FN_10_CFG_TML_MNT    = 0x100A,       // 转发主站直接对终端的遥控跳闸/允许合闸命令
    CMD_AFN_G_FN_11_CFG_TML_MNT    = 0x100B,       // 转发主站直接对终端的遥控送电命令

    /* 在这之上添加扩展命令字 */
    CMD_AFN_FN_MAX                                 // 
}eMtCmd;

typedef enum
{
	AFN_00_CONF  = 0x00,     // 确认否认
	AFN_01_RSET  = 0x01,     // 复位
	AFN_02_LINK  = 0x02,     // 接口检测
	AFN_03_RELY  = 0x03,     // 中继站命令
	AFN_04_SETP  = 0x04,     // 设置参数
	AFN_05_CTRL  = 0x05,     // 控制命令
	AFN_06_AUTH  = 0x06,     // 身份认证
	AFN_08_CASC  = 0x08,     // 请求被级联终端主动上报 
	AFN_09_CFIG  = 0x09,     // 请求终端配置
	AFN_0A_GETP  = 0x0A,     // 查询参数
	AFN_0B_ASKT  = 0x0B,     // 请求任务数据
	AFN_0C_ASK1  = 0x0C,     // 请求1类数据 实时数据
	AFN_0D_ASK2  = 0x0D,     // 请求2类数据 历史数据
	AFN_0E_ASK3  = 0x0E,     // 请求3类数据 事件数据
	AFN_0F_FILE  = 0x0F,     // 文件传输
	AFN_10_DATA  = 0x10,     // 数据转发
    AFN_MAX,
	AFN_NULL     = 0xFF,     // 没有对应的答复类型 ，不答复             
	
}eMtAFN; //  应用层功能码AFN


typedef enum
{
	MT_OK,             // 无错误                 0 
	MT_NULL,           // 指针为空               1 
	MT_OUT_RNG,        // 参数越界    2
	MT_NONE,           // 不存在,没有找到    3    
	MT_ERR_IO,         // IO错误              4
	MT_ERR_RES,        // 资源不足6
	MT_ERR_INIT,       // 没有初始化7
	MT_ERR_PARA,       // 参数错误8
	MT_ERR_FN,         // 指定Afn 中不支持的 Fn9
	MT_ERR_PN,         // 指定Afn Fn 中不支持的 Pn10
	MT_ERR_ADDR,       // 无效地址
	MT_ERR_CTRL,       // 控制域错误 
	MT_ERR_SEQ,        // SEQ域错误13
	MT_ERR_SEQ2CS,     // 14
	MT_ERR_AFN,        // AFN 错误15
	MT_ERR_UNCOMP,     // 不完整的协议包16
	MT_ERR_0x68,       // 错误的报文起始17
    MT_ERR_PROTO,      // 错误的协议标识18
    MT_ERR_CS,         // 错误的检测和19
    MT_ERR_0x16,       // 错误的结尾符20
    MT_ERR_LOGIC,      // 错误的处理逻辑
    MT_ERR_PACK,       // 不是一个有效的包

    
}eMtErr;  // MT 模块返回码

typedef enum
{

	MT_POS_UNKOWN, // 未知帧位置信息
	MT_POS_SIGLE,  // 单帧
	MT_POS_MUL_S,  // 多帧起始帧，有后续帧
	MT_POS_MUL_M,  // 多帧中间帧
	MT_POS_MUL_E,  // 多帧最后帧
	
}eMtFmPos; // 帧的位置类型


typedef enum
{
	MT_PN_UNKOWN,       // 未知PN 类型
	MT_PN_0,            // P0
	MT_PN_TM,           // 终端号
	MT_PN_TP,           // 测量点号 test point
	MT_PN_GT,           // 总加组号 GROUP_TOTAL
	MT_PN_CT,           // 控制轮次 control times
	MT_PN_TK,           // 任务号 task number
	MT_PN_DN,           // 直流模拟量端口号 direct current simulation port number
}eMtPn;


typedef struct
{

	UINT8 ucDA1;         // 信息点元
	UINT8 ucDA2;         // 信息点组
	UINT8 ucDT1;         // 信息类元
	UINT8 ucDT2;         // 信息类组
}sMtDaDt;

typedef struct
{
	UINT16 usPn;         // Pn
	UINT16 usFn;         // Fn
}sMtPnFn;


typedef struct
{
    UINT8 ucEC1; // 重要事件计数器
    UINT8 ucEC2; // 一般事件计数器
    
}sMtEC;    // 事件计数器  

typedef enum
{
	MT_DIR_UNKOWN,   // 未知报文方向
	MT_DIR_M2S,      // 主动站到从动站    下行
	MT_DIR_S2M,      // 从动站到主动站    上行
	MT_DIR_ALL,      // 正向与反向
	
}eMtDir;

typedef enum
{
	//MT_TRANS_UNKOWN,    // 未知方向
	MT_TRANS_U2F,       // 用户侧数据结构到帧数据结构
	MT_TRANS_F2U,       // 帧侧数据结构到用户侧数据结构	
}eMtTransDir;             // 用户侧与帧侧数据结构转换函数

/*  数据单元格式定义 */
typedef struct
{

	UINT8 ssBCD_0:4;  // 秒
	UINT8 ssBCD_1:4;
	UINT8 mmBCD_0:4;  // 分
	UINT8 mmBCD_1:4;
	UINT8 hhBCD_0:4;  // 时
	UINT8 hhBCD_1:4;
	UINT8 ddBCD_0:4;  // 日
	UINT8 ddBCD_1:4;
	UINT8 MMBCD_0:4;  // 月
	UINT8 MMBCD_1:1;  
	UINT8 wwBCD_0:3;  // 星期
	UINT8 yyBCD_0:4;  // 年
	UINT8 yyBCD_1:4;
}sMtFmt01;   // 一共6个字节


// 数据格式02
typedef struct
{

	UINT8 BCD_0:4;
	UINT8 BCD_1:4;
	UINT8 ucG321:3;
	UINT8 signal:1;
	UINT8 BCD_2:4;
}sMtFmt02;

typedef struct
{

	UINT8 BCD_0:4;
	UINT8 BCD_1:4;
	UINT8 BCD_2:4;
	UINT8 BCD_3:4;
	UINT8 BCD_4:4;
	UINT8 BCD_5:4;
	UINT8 BCD_6:4;
	UINT8 S:1;
	UINT8 Res0:1;
	UINT8 G:1;
	UINT8 Res1:1;

}sMtFmt03;

typedef struct
{

	UINT8 BCD_0:4;  // BCD 个位
	UINT8 BCD_1:3;  // BCD 十位(0-7)
	UINT8 S0:1;     // S0定义：S0=0，表示上浮；S0=1，表示下浮。

}sMtFmt04;

typedef struct
{

	UINT8 BCD_0_1:4; 	// BCD 十分位
	UINT8 BCD_0  :4;	// BCD 个位
	UINT8 BCD_1  :4;	// BCD 十位
	UINT8 BCD_2  :3;	// BCD 百位
	UINT8 S      :1;	// BCD 符号位
}sMtFmt05;

typedef struct
{

	UINT8 BCD_0_2:4;   // 百分位
	UINT8 BCD_0_1:4;   // 十分位
	UINT8 BCD_0:4;     // 个位
	UINT8 BCD_1:3;     // 十位
	UINT8 S:1;         // 正负

}sMtFmt06;

typedef struct
{
	UINT8 BCD_0_1:4;  // BCD 十分位
	UINT8 BCD_0  :4;  // BCD 个位
	UINT8 BCD_1  :4;  // BCD 十位
	UINT8 BCD_2  :4;  // BCD 百位

}sMtFmt07;

typedef struct
{

	UINT8 BCD_0:4;  // BCD个位
	UINT8 BCD_1:4;  // BCD十位
	UINT8 BCD_2:4;  // BCD百位
	UINT8 BCD_3:4;  // BCD千位
}sMtFmt08;

typedef struct
{

	UINT8 BCD_0_4:4;  // BCD 万分位
	UINT8 BCD_0_3:4;  // BCD 千分位
	UINT8 BCD_0_2:4;  // BCD 百分位
	UINT8 BCD_0_1:4;  // BCD 十分位
	UINT8 BCD_0  :4;  // BCD 个位
	UINT8 BCD_1  :3;  // BCD 十位
    UINT8 S      :1;  // 符号位
}sMtFmt09;

typedef struct
{

	UINT8 BCD_0:4;   //BCD 个位
	UINT8 BCD_1:4;   //BCD 十位
	UINT8 BCD_2:4;   //BCD 百位
	UINT8 BCD_3:4;   //BCD 千位
	UINT8 BCD_4:4;   //BCD 万位
	UINT8 BCD_5:4;   //BCD 十万位

}sMtFmt10;

typedef struct
{

	UINT8 BCD_0_2:4;   // BCD 百分位
	UINT8 BCD_0_1:4;   // BCD 十分位
	UINT8 BCD_0  :4;   //BCD 个位
	UINT8 BCD_1  :4;   //BCD 十位
	UINT8 BCD_2  :4;   //BCD 百位
	UINT8 BCD_3  :4;   //BCD 千位
	UINT8 BCD_4  :4;   //BCD 万位
	UINT8 BCD_5  :4;   //BCD 十万位

}sMtFmt11;

typedef struct
{

	UINT8 BCD_0 :4;    //BCD 个位
	UINT8 BCD_1 :4;    //BCD 十位
	UINT8 BCD_2 :4;    //BCD 百位
	UINT8 BCD_3 :4;    //BCD 千位
	UINT8 BCD_4 :4;    //BCD 万位
	UINT8 BCD_5 :4;    //BCD 十万位
	UINT8 BCD_6 :4;    //BCD 百万位
	UINT8 BCD_7 :4;    //BCD 千万位
	UINT8 BCD_8 :4;    //BCD 亿位
	UINT8 BCD_9 :4;    //BCD 十亿位
	UINT8 BCD_10:4;    //BCD 百亿位
	UINT8 BCD_11:4;    //BCD 千亿位
}sMtFmt12;


typedef struct
{

	UINT8 BCD_0_4:4;   // BCD 万分位
	UINT8 BCD_0_3:4;   // BCD 千分位
	UINT8 BCD_0_2:4;   // BCD 百分位
	UINT8 BCD_0_1:4;   // BCD 十分位
	UINT8 BCD_0  :4;   //BCD 个位
	UINT8 BCD_1  :4;   //BCD 十位
	UINT8 BCD_2  :4;   //BCD 百位
	UINT8 BCD_3  :4;   //BCD 千位

}sMtFmt13;


typedef struct
{

	UINT8 BCD_0_4:4;   // BCD 万分位
	UINT8 BCD_0_3:4;   // BCD 千分位
	UINT8 BCD_0_2:4;   // BCD 百分位
	UINT8 BCD_0_1:4;   // BCD 十分位
	UINT8 BCD_0  :4;   //BCD 个位
	UINT8 BCD_1  :4;   //BCD 十位
	UINT8 BCD_2  :4;   //BCD 百位
	UINT8 BCD_3  :4;   //BCD 千位
	UINT8 BCD_4 :4;    //BCD 万位
	UINT8 BCD_5 :4;    //BCD 十万位

}sMtFmt14;

typedef struct
{

	UINT8 mmBCD_0:4;  // 分
	UINT8 mmBCD_1:4;
	UINT8 hhBCD_0:4;  // 时
	UINT8 hhBCD_1:4;
	UINT8 ddBCD_0:4;  // 日
	UINT8 ddBCD_1:4;
	UINT8 MMBCD_0:4;  // 月
	UINT8 MMBCD_1:4;  
	UINT8 yyBCD_0:4;  // 年
	UINT8 yyBCD_1:4;

}sMtFmt15;

typedef struct
{

	UINT8 ssBCD_0:4;  // 秒
	UINT8 ssBCD_1:4;
	UINT8 mmBCD_0:4;  // 分
	UINT8 mmBCD_1:4;
	UINT8 hhBCD_0:4;  // 时
	UINT8 hhBCD_1:4;
	UINT8 ddBCD_0:4;  // 日
	UINT8 ddBCD_1:4;

}sMtFmt16;

typedef struct
{

	UINT8 mmBCD_0:4;  // 分
	UINT8 mmBCD_1:4;
	UINT8 hhBCD_0:4;  // 时
	UINT8 hhBCD_1:4;
	UINT8 ddBCD_0:4;  // 日
	UINT8 ddBCD_1:4;
	UINT8 MMBCD_0:4;  // 月
	UINT8 MMBCD_1:4;  
}sMtFmt17;

typedef struct
{

	UINT8 mmBCD_0:4;  // 分
	UINT8 mmBCD_1:4;
	UINT8 hhBCD_0:4;  // 时
	UINT8 hhBCD_1:4;
	UINT8 ddBCD_0:4;  // 日
	UINT8 ddBCD_1:4;
}sMtFmt18;

typedef struct
{

	UINT8 mmBCD_0:4;  // 分
	UINT8 mmBCD_1:4;
	UINT8 hhBCD_0:4;  // 时
	UINT8 hhBCD_1:4;
}sMtFmt19;

typedef struct
{

	UINT8 ddBCD_0:4;  // 日
	UINT8 ddBCD_1:4;
	UINT8 MMBCD_0:4;  // 月
	UINT8 MMBCD_1:4;  
	UINT8 yyBCD_0:4;  // 年
	UINT8 yyBCD_1:4;

}sMtFmt20;

typedef struct
{

	UINT8 MMBCD_0:4;  // 月
	UINT8 MMBCD_1:4;  
	UINT8 yyBCD_0:4;  // 年
	UINT8 yyBCD_1:4;

}sMtFmt21;


typedef struct
{

	UINT8 BCD_0_1:4;  // 十分位
	UINT8 BCD_0  :4;  // 个位

}sMtFmt22;

typedef struct
{

	UINT8 BCD_0_4:4;   // BCD 万分位
	UINT8 BCD_0_3:4;   // BCD 千分位
	UINT8 BCD_0_2:4;   // BCD 百分位
	UINT8 BCD_0_1:4;   // BCD 十分位
	UINT8 BCD_0  :4;   //BCD 个位
	UINT8 BCD_1  :4;   //BCD 十位
}sMtFmt23;

typedef struct
{

	UINT8 hhBCD_0:4;  // 时
	UINT8 hhBCD_1:4;
	UINT8 ddBCD_0:4;  // 日
	UINT8 ddBCD_1:4;
}sMtFmt24;

typedef struct
{

	UINT8 BCD_0_3:4;  // BCD 千分位
	UINT8 BCD_0_2:4;  // BCD 百分位
	UINT8 BCD_0_1:4;  // BCD 十分位
	UINT8 BCD_0  :4;  // BCD 个位
	UINT8 BCD_1  :3;  // BCD 十位
    UINT8 S      :1;  // 符号位
}sMtFmt25;

typedef struct
{

	UINT8 BCD_0_3:4;  // BCD 千分位
	UINT8 BCD_0_2:4;  // BCD 百分位
	UINT8 BCD_0_1:4;  // BCD 十分位
	UINT8 BCD_0  :4;  // BCD 个位

}sMtFmt26;


typedef struct
{

	UINT8 BCD_0 :4;    //BCD 个位
	UINT8 BCD_1 :4;    //BCD 十位
	UINT8 BCD_2 :4;    //BCD 百位
	UINT8 BCD_3 :4;    //BCD 千位
	UINT8 BCD_4 :4;    //BCD 万位
	UINT8 BCD_5 :4;    //BCD 十万位
	UINT8 BCD_6 :4;    //BCD 百万位
	UINT8 BCD_7 :4;    //BCD 千万位

}sMtFmt27;


typedef struct
{

	UINT8 ucIP1;
	UINT8 ucIP2;
	UINT8 ucIP3;
	UINT8 ucIP4;
}sMtIP;

typedef struct
{

	UINT8 ucMask1;
	UINT8 ucMask2;
	UINT8 ucMask3;
	UINT8 ucMask4;
}sMtMask;




/***************************************************************************
 * 逐个确认与否认
 *
{*///

// 用户侧数据
typedef struct
{
	eMtCmd  eCmd;         // Fn  1 ~ 241
	UINT16  usPn;         // Pn  0 ~ 2033
	BOOL    bOk;
}sMtuFnPnErr;   // 确认与否认 用户侧数据结构

typedef struct
{
	eMtAFN      eAFN;        // 需要确认的AFN
	UINT8       ucNum;        // 需要确认 或 否认的 Fn个数
    sMtuFnPnErr sOne[1];  // ucNum 个sMtUFnPnErr
}sMtOnebyOne;                 // 用户侧 Afn00 F3数据结构




// 帧侧数据
typedef struct
{
	sMtDaDt sDaDt;  // 数据单元标识
	UINT8   ucErr;  // 错误 标识                  0 正确 1 错误
}sMtOne_f;       // 确认与否认 帧侧数据结构   

typedef struct
{
	UINT8    ucAFN;
	sMtOne_f sOne[1];
}sMtOneByOne_f;


// 转换函数
eMtErr emtTrans_OneByOne(eMtTransDir eDir,void *psUser, void *psFrame, UINT16 *pusfLen);
///*}


// afn = 04H 
typedef struct
{

	UINT8  ucRTS;        // 终端数传机延时时间RTS
	UINT8  ucRTM;        // 终端作为启动站允许发送传输延时时间 slave recieve time out minute
	UINT8  ucSWTS1;      // 终端等待从动站响应的超时时间和重发次数 wait ts
    UINT8  ucSWTS2;      // 终端等待从动站响应的超时时间和重发次数 wait ts
	UINT8  bs8Con;       // 需要主站确认的通信服务（CON=1）的标志
	UINT8  ucHeartBeat;  // 心跳周期

}sMtAfn04F1_ConUpPortPara_f;  //上行通信口通信参数设置数据单元格式 (AFN04_F1)    帧侧数据


typedef struct
{
    UINT8  ucRTS;             // 终端数传机延时时间RTS
	UINT8  ucRTM;             // 终端作为启动站允许发送传输延时时间 slave recieve time out minute
	UINT8  ucReSendTimes;     // 重发次数 (0~3)   0 表示不允许重发
	UINT8  ucHeartBeat;       // 心跳周期
    UINT16 usTmWaitTimeoutS;  // 集中器等待从动站响应的超时时间 秒数 0~4095
    BOOL   bAutoReportAsk_1;  // 允许自动上报1类数据，同时需要主站确认
    BOOL   bAutoReportAsk_2;  // 允许自动上报2类数据，同时需要主站确认
    BOOL   bAutoReportAsk_3;  // 允许自动上报3类数据，同时需要主站确认

}sMtAfn04F1_ConUpPortPara_u; //上行通信口通信参数设置数据单元格式 (AFN04_F1)    用户侧数据


typedef struct
{

	UINT8  ucPermit   :1;        // 允许∕禁止：由第1字节的 D7表示允许或禁止终端转发，置"0"：禁止，置 "1"：允许。
	UINT8  ucAddrCount:7;        // 被转发的终端地址数n：由第1字节的D0～D6位表示，数值范围0～16。
	UINT16 usAddress[1];         // 被转发终端地址：每个地址为2字节，与终端地址A2定义相同
	//UINT16 usAddress[0];         // 被转发终端地址：每个地址为2字节，与终端地址A2定义相同

}sMtAfn04F2_ConUpPortParaWireless_f; // 上行通信无线中继转发设置数据单元格式(AFN04_F2) 


typedef struct
{

	BOOL   bPermit;           // 允许∕禁止：由第1字节的 D7表示允许或禁止终端转发，置"0"：禁止，置 "1"：允许。
	UINT8  ucAddrCount;       // 被转发的终端地址数n：由第1字节的D0～D6位表示，数值范围0～16。
	UINT16 usAddress[16];     // 被转发终端地址：每个地址为2字节，与终端地址A2定义相同

}sMtAfn04F2_ConUpPortParaWireless_u; // 上行通信无线中继转发设置数据单元格式(AFN04_F2) 





typedef struct
{
	UINT8  ucMainIP[4];     // 主用地址
	UINT16 usMainPort;      // 主用端口
	UINT8  ucBackIP[4];	    // 备用地址
	UINT16 usBackPort;      // 备用端口	
	UINT8  ucascAPN[16];    //    
}sMtAfn04F3_MasterIpPort_f;    // 主站IP地址和端口数据单元格式


typedef struct
{
	UINT32  ulMainIP;        // 主用地址
	UINT16  usMainPort;      // 主用端口
	UINT32  ulBackIP;	     // 备用地址
	UINT16  usBackPort;      // 备用端口	
	UINT8   ucascAPN[16];    //    
}sMtAfn04F3_MasterIpPort_u;    // 主站IP地址和端口数据单元格式




/*  sMtAfn04F4_MstSmSTelephoneSm_u

--普通电话信道：前8字节有效，代表16位电话号码，后8字节无效，
  每位号码数据范围0至B：0～9表示电话号码0……9；A为"，"，代表拨号停顿（延时）；B为"#"。
--GSM/CDMA信道：前8字节代表主站手机电话号码，后8字节代表短消息服务中心电话号码。
--Z0～Z15对应电话号码第一位至最末位，余下未填满部分填FH。

*/

typedef struct
{

    UINT8 ucPhoneMaster[17]; // 主站电话号码         最长支持16位电话号码
    UINT8 ucPhoneSMS[17];    // 短信服务中心电话号码 最长支持16位电话号码

}sMtAfn04F4_MstSmsPhone_u;   // 主站电话、短信号码数据单元格式

typedef struct
{

    UINT8 bcdPhoneMaster[8];
    UINT8 bcdPhoneSMS[8]; 

}sMtAfn04F4_MstSmsPhone_f;   // 主站电话、短信号码数据单元格式


typedef struct
{

	UINT8  ucSchemeNum; 
	UINT16 usPara;

}sMtAfn04F5_UpMsgAuth_u;   //上行通信消息认证参数设置数据单元格式

typedef struct
{

	UINT8  ucSchemeNum; 
	UINT16 usPara;

}sMtAfn04F5_UpMsgAuth_f;   //上行通信消息认证参数设置数据单元格式



// afn04_f6 终端组地址设置数据单元格式
typedef struct
{

	UINT32 ulGroupAddress[8];

}sMtAfn04F6_ConGroupAddr_u; 

typedef struct
{

	UINT32 ulGroupAddress[8];

}sMtAfn04F6_ConGroupAddr_f; 


// afn04_f7 集中器IP地址和端口 参数设置
typedef struct
{

	sMtIP    sTmIp;
	sMtIP    sMask;
	sMtIP    sGate;
	UINT8    ucAgent;
	sMtIP    sAgentSever;
	UINT16   usAgnetPort;
	UINT8    ucAgentLink;
	UINT8    ucUserNameLen;   // 0~20 0 时表示没有用户名 为非0时表示此时需要用户名验证
    /*  下列数据结构为变长
	UINT8    aUserName[ucUserNameLen];   
	UINT8    ucPassWordLen;  // 0~20   0时表示没有密码，为非0 时表示此时需要密码验证
	UINT8    aPassWord[ucPassWordLen];
	UINT16   usTmLisenPort;
	*/
}sMtAfn04F7_ConIpPort_f;

typedef struct
{

	sMtIP    sTmIp;
	sMtIP    sMask;
	sMtIP    sGate;
	UINT8    ucAgent;
	sMtIP    sAgentSever;
	UINT16   usAgnetPort;
	UINT8    ucAgentLink;
	UINT16   usTmLisenPort;
	UINT8    aUserName[21];   // 最长支持20位用户名 可以为空，表示不需要用户名验证   
	UINT8    aPassWord[21];   // 最长支持20位密码验证 可以为空，表示不需要密码验证

}sMtAfn04F7_ConIpPort_u;



// 集中器上行通信工作方式（以太专网或虚拟专网）
typedef struct
{

	UINT8  bs8WorkWay;
	UINT16 usTimeInterval;
	UINT8  ucReCallTimes;
	UINT8  ucAutoDropTime;
	UINT8  bs24Permit[3];
}sMtAfn04F8_ConUpComWay_f;


typedef struct
{

	UINT8  bs8WorkWay;
	UINT16 usTimeInterval;
	UINT8  ucReCallTimes;
	UINT8  ucAutoDropTime;
	UINT8  bs24Permit[3];
}sMtAfn04F8_ConUpComWay_u;



// 集中器与终端通信读取数据运行参数设置
typedef struct
{

	UINT8 bs64EventRecord[8];
	UINT8 bs64EventWeight[8];

}sMtAfn04F9_Con2TmlComPara_f;

typedef struct
{

	UINT8 bs64EventRecord[8];
	UINT8 bs64EventWeight[8];

}sMtAfn04F9_Con2TmlComPara_u;



// 集中器下行通信模块的参数设置
typedef struct
{

}sMtAfn04F10_ConDownPara_u;



typedef struct
{

}sMtAfn04F10_ConDownPara_f;


// 虚拟专网用户名、密码
typedef struct
{

}sMtAfn04F11_VpnPwd_u;

typedef struct
{

}sMtAfn04F11_VpnPwd_f;


// 集中器上行通信流量门限设置
typedef struct
{

}sMtAfn04F12_ConUpLimit_f;

typedef struct
{

}sMtAfn04F12_ConUpLimit_u;




typedef struct
{

	UINT16 usConfigCount;
    UINT16 usDevSerNum;
	UINT16 usTestPoint;
	UINT8  ucPort;
	UINT8  ucProtocol;
	UINT8  ucbcdIP[4];
	//UINT8 

}sMtAfn04F10_TmMeterConfig;  // 终端电能表/交采装置配置数据单元格式




typedef struct
{

	UINT8  ucInputPort;   // 脉冲输入端口号
	UINT8  ucTestPoint;   // 所属测量点号
	UINT8  bs8PulseWord;  // 脉冲属性
	UINT16 usMeterK;      // 电表常数k

}sMtTmPulseConfig;

typedef struct
{

	UINT8 ucItemCount;   // 本次脉冲配置路数n
	//sMtTmPulseConfig  sItem[0];
	sMtTmPulseConfig  sItem[1];
	
}sMtAfn04F11_TmPulseConfig;

typedef struct
{

	UINT8 bs8StateAccess;
	UINT8 bs8StateAttr;

}sMtAfn04F12_TmStateInput;  // 终端状态量输入参数数据单元格式

typedef struct
{

	UINT8 ucItemN;
	
}sMtAfn04F13_TmVoltElecAnalog;   // 终端电压/电流模拟量配置参数

typedef struct
{

	UINT8 ucItemN;

}sMtAfn04F14_TmGroupTotal; // 终端总加组配置参数数据单元格式

typedef struct
{

	UINT8 ucItemN;

}sMtAfn04F15_HaveLimitEvent;     // 有功总电量差动越限事件参数设置数据单元格式

typedef struct
{

	UINT8 strUserName[32];
	UINT8 strPassword[32];

}sMtAfn04F16_VpnUser;//虚拟专网用户名、密码数据单元格式

typedef struct
{

	sMtFmt02 sFmt02;
	
}sMtAfn04F17_TmGuardValue;

typedef struct
{

	UINT8 bs8CtrlWord[12];
}sMtAfn04F18_TmPowerCtrl; // 终端功控时段数据单元格式

typedef struct
{

	sMtFmt04 sFmt04;
}sMtAfn04F19_TmPeriodPowerCtrl; //时段功控定值浮动系数数据单元格式

typedef struct
{

	sMtFmt04 sFmt04;
}sMtAfn04F20_TmMonthPowerCtrl; // 月电量控定值浮动系数数据单元格式

typedef struct
{

	UINT8 ucRateID[48];
	UINT8 ucRateNum;

}sMtAfn04F21_TmPeriodRate; // 电能量费率时段和费率数数据单元格式

typedef struct
{

	UINT8 ucRateNum;
	//sMtFmt03 sFmt03[0];  // ucRateNum 个
	sMtFmt03 sFmt03[1];  // ucRateNum 个

}sMtAfn04F22_TmPowerRate;  // 终端电能量费率数据单元格式

typedef struct
{

	UINT8 bs24Alarm[3];

}sMtAfn04F23_TmPayAlarm; // 终端催费告警参数数据单元格式



typedef struct
{
	UINT16   usVtRatio;// voltage transformer; potential transformer
    UINT16   usCtRatio;// current transformer
    sMtFmt06 sVR;      // voltage rating; rated voltage; nominal voltage 
    sMtFmt22 sCR;       // 额定电流       rated current; current rating
}sMtAfn04F25_TestPoint; // 测量点基本参数数据单元格式


typedef struct
{
	sMtFmt07 sQVMax;    // 电压合格上限
	sMtFmt07 sQVMin;    // 电压合格下限
	sMtFmt07 sDropV;    // 电压断相门限
	sMtFmt07 sOverV;    // 过压门限
	UINT8    ucOverVmm; // 越限持续时间
	sMtFmt05 sOverVrec; // 越限恢复系数
	sMtFmt07 sLessV;    // 电压下下限（欠压门限）
     
}sMtAfn04F26_TestPointLimit; // 测量点限值参数数据单元格式

typedef struct
{

	sMtFmt26 sRa;
	sMtFmt26 sXa;
	sMtFmt26 sGa;
	sMtFmt26 sBa;
	sMtFmt26 sRb;
	sMtFmt26 sXb;
	sMtFmt26 sGb;
	sMtFmt26 sBb;
	sMtFmt26 sRc;
	sMtFmt26 sXc;
	sMtFmt26 sGc;
	sMtFmt26 sBc;
}sMtAfn04F27_TpCopperIronLoss;//测量点铜损、铁损参数数据单元格式

/*
 * 数据名称: double 类型的合成与解合成
 * 数据说明: 浮点数在机内用指数型式表示，分解为：数符，尾数，指数符，指数四部分。 
 *   无论是单精度还是双精度在存储中都分为三个部分：
	1.符号位(Sign) : 0代表正，1代表为负 
	2.指数位（Exponent）:用于存储科学计数法中的指数数据，并且采用移位存储 
	3.尾数部分（Mantissa）：尾数部分 
{*///

typedef union 
{
	double v;
	struct 
	{
		unsigned mantissa2 : 32;
		unsigned mantissa1 : 20;
		unsigned exponent : 11;
		unsigned sign :  1;
	} s;
}uMtDoubleFmt;


int    bMtGetDoubleSign(double dVal);              // 取得一个double的符号位 sign = -1 / +1
void   vMtSetDoubleSign(double *pdVal, int sign);  // 设置一个浮点数的符号位 sign = -1 / +1

///*}

/*
 * 数据名称: (+/-) 百万 * 10(4 ~ -4)  
 * 数据范围: (+/-) 9999.999 ~ 99999990000   
 * 数据说明: 用户侧时需要用Double  
 * float   : 1bit（符号位） 8bits （指数位） 23bits（尾数位）   2^23 = 8388608
 * double  : 1bit（符号位） 11bits（指数位） 52bits（尾数位）   2^52 = 4503599627370496
 * 转换函数: bMtTrans_fmtsMillion_to_double
 *           bMtTrans_double_to_fmtsMillion  
 * 数据格式: 
 *
	+--------+----+----+----+----+----+----+----+----+
	|        | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
	+--------+----+----+----+----+----+----+----+----+
	| BYTE 1 |     BCD码十位     |   BCD 码个位      |
	+--------+----+----+----+----+----+----+----+----+
	| BYTE 2 |     BCD码千位     |   BCD 码百位      |
	+--------+----+----+----+----+----+----+----+----+
	| BYTE 3 |    BCD码十万位    |   BCD 码万位      |
	+--------+----+----+----+----+----+----+----+----+
	| BYTE 4 | G3 | G2 | G1 | S  |   BCD 码百万位    |
	+--------+----+----+----+----+----+----+----+----+
	

	+-------+-------+-------+----------+
	|   G3  |  G2   |  G1   |   含义   |
	+-------+-------+-------+----------+
	|   0   |   0   |   0   |   10(4)  |
	+-------+-------+-------+----------+
	|   0   |   0   |   0   |   10(3)  |
	+-------+-------+-------+----------+
	|   0   |   0   |   0   |   10(2)  |
	+-------+-------+-------+----------+
	|   0   |   0   |   0   |   10(1)  |
	+-------+-------+-------+----------+
	|   0   |   0   |   0   |   10(0)  |
	+-------+-------+-------+----------+
	|   0   |   0   |   0   |   10(-1) |
	+-------+-------+-------+----------+
	|   0   |   0   |   0   |   10(-2) |
	+-------+-------+-------+----------+
	|   0   |   0   |   0   |   10(-3) |
	+-------+-------+-------+----------+

   S 符号位:S = 0 正数 S = 1 表示负数
	
{*///

typedef struct
{
	UINT8 BCD_0 :4;    // BCD 个位
	UINT8 BCD_1 :4;    // BCD 十位
	UINT8 BCD_2 :4;    // BCD 百位
	UINT8 BCD_3 :4;    // BCD 千位
	UINT8 BCD_4 :4;    // BCD 万位
	UINT8 BCD_5 :4;    // BCD 十万位
	UINT8 BCD_6 :4;    // BCD 百万位
	UINT8 S     :1;    // 符号位      0 为正 1 为负
	UINT8 G1    :1;    // 指数bit 0
	UINT8 G2    :1;    // 指数bit 1
	UINT8 G3    :1;    // 指数符号位
}sMtFmtsMillion;


#define MT_SMILLION_MIN -99999990000.0
#define MT_SMILLION_MAX  99999990000.0


BOOL   bMtTrans_fmtsMillion_to_double(sMtFmtsMillion *psMtFmtsMillion, double *pdValue);
eMtErr eMtTrans_double_to_fmtsMillion(double dValue, int nExp, sMtFmtsMillion *psMtFmtsMillion);
int  nMtPow(UINT8 exp);   // 10 exp次方 exp < 10

///*}


/* 
 * 数据名称:非电气量参数配置  
 * 命令类型:CMD_AFN_4_FN_33_CFG_NOT_ELEC
 * 数据说明:非电气量统一用该数据结构来解析
 * 1：温度，2：流量，3：流速，4：压力，5：湿度，6：照度，7：转速，其他：备用
{*///

typedef enum
{
	MT_NELEC_UNKOWN,  // 未知非电气量
	MT_NELEC_TEMP,    // 温度
	MT_NELEC_FLOW,    // 流量
	MT_NELEC_FLOW_V,  // 流速
    MT_NELEC_PRESS,   // 压力
	MT_NELEC_HUMID,   // 湿度 humidity
	MT_NELEC_ILLUM,   // 照度 illumination
	MT_NELEC_ROTATE,  // 转速 rotate speed
}eMtNotElec;

#define MT_NOT_ELEC_RANG_MAX   99999990000.0
#define MT_NOT_ELEC_RANG_MIN  -99999990000.0

typedef struct
{
	eMtNotElec eType;  // 类型
	double     dMin;   // 量程下限  不能小于 MT_NOT_ELEC_RANG_MIN
	double     dMax;   // 量程上限  不能大于 MT_NOT_ELEC_RANG_MAX
	
}sMtCfgNotElec;   


typedef struct
{
	UINT8          ucType;
	sMtFmtsMillion sMin;
	sMtFmtsMillion sMax;
}sMtCfgNotElec_f; 

eMtErr emtTrans_CfgNotElecValue(eMtTransDir eDir,void *psUser, void *psFrame, UINT16 *pusfLen);
///*} 非电气量参数配置




/* 
 * 数据名称:非电气量  
 * 命令类型:CMD_AFN_C_FN_90_NOT_ELEC
 * 数据说明:非电气量统一用该数据结构来解析
 * 1：温度，2：流量，3：流速，4：压力，5：湿度，6：照度，7：转速，其他：备用
{*///


typedef struct
{	
	eMtNotElec eType;    // 类型
	double     dValue;   // 数据
}sMtNotElec;   


typedef struct
{
	UINT8          ucType;
	sMtFmtsMillion sValue;
}sMtNotElec_f; 

eMtErr emtTrans_NotElecValue(eMtTransDir eDir,void *psUser, void *psFrame, UINT16 *pusfLen);
///*} 非电气量参数配置





typedef struct
{


	UINT8 ucLimitPowerTime:4; // 限电时间
	UINT8 ucHoldAlarmTime :4; // 告警延时时间
	
}sMtAfn05F1_RemoteCtrlTrip_f; // 遥控跳闸数据单元格式


typedef struct
{

	UINT8 ucLimitPowerTime;   // 限电时间 数值范围0～15，单位：0.5h（半个小时），
	                          //为0时，表示紧急跳闸，即长时间跳闸，不自动解除跳闸状态；
	                          //不为0时，按设置的限电时间进行限电。
	UINT8 ucHoldAlarmTime;    // 告警延时时间 
	                          // 数值范围0～15，单位：min，为"0"时，表示立即跳闸；
	                          // 不为0时，按设置的告警时间进行告警。
	
}sMtAfn05F1_RemoteCtrlTrip_u; // 遥控跳闸数据单元格式



typedef struct
{

	UINT8 bs8Word;
    UINT8 ucWay;

}sMtAfn05F9_PeriodPowerCtrl;  // 时段功控投入数据单元格式



typedef struct
{
    UINT8 ssBCD_0:4;  // 秒
	UINT8 ssBCD_1:4;
	UINT8 mmBCD_0:4;  // 分
	UINT8 mmBCD_1:4;
	UINT8 hhBCD_0:4;  // 时
	UINT8 hhBCD_1:4;
	UINT8 ddBCD_0:4;  // 日
	UINT8 ddBCD_1:4;
	UINT8 MMBCD_0:4;  // 月
	UINT8 MMBCD_1:1;  
	UINT8 wwBCD_0:3;  // 星期
	UINT8 yyBCD_0:4;  // 年
	UINT8 yyBCD_1:4;

}sMtAfn05F31_TimeTick_f;  // 对时命令数据结构 用户侧


typedef struct
{
    UINT8 ucYY;   // year   格式 YY
    UINT8 ucMM;   // month  月 
    UINT8 ucWW;   // weak   星期  0 表示无效  1 - 7
    UINT8 ucDD;   // Day    日
    UINT8 ucHH;   // hour   时
    UINT8 ucmm;   // minute 分钟
    UINT8 ucss;   // second 秒
    
}sMtAfn05F31_TimeTick_u;  // 对时命令数据结构 用户侧


typedef struct
{
    UINT8 ucPort;    // 1 - 31
}sMtAfn05F49_PortSuspend_u;



typedef struct
{
    UINT8 ucPort;    // 1 - 31
}sMtAfn05F49_PortSuspend_f;




typedef struct
{
    UINT8 ucPort;    // 1 - 31
}sMtAfn05F50_PortResume_u;



typedef struct
{
    UINT8 ucPort;    // 1 - 31
}sMtAfn05F50_PortResume_f;



typedef struct
{
    UINT8 ucPort;    // 1 - 31
}sMtAfn05F51_PortAgain_u;


typedef struct
{
    UINT8 ucPort;    // 1 - 31
}sMtAfn05F51_PortAgain_f;





// 身份认证请求及应答
typedef struct
{
    UINT8 aCiphertext[16];
}sMtAfn06F1_IdAuthQ_u;

typedef struct
{
    UINT8 aCiphertext[16];
}sMtAfn06F1_IdAuthQ_f;

typedef struct
{
    UINT8 aCiphertext[16];
}sMtAfn06F2_IdAuthA_f;

typedef struct
{
    UINT8 aCiphertext[16];
}sMtAfn06F2_IdAuthA_u;



// 随机数请求与应答
typedef struct
{
    UINT8 aCiphertext[16];
}sMtAfn06F3_RandQ_f;

typedef struct
{
    UINT8 aCiphertext[16];
}sMtAfn06F3_RandQ_u;

typedef struct
{
    UINT8 aCiphertext[16];
}sMtAfn06F4_RandA_f;

typedef struct
{
    UINT8 aCiphertext[16];
}sMtAfn06F4_RandA_u;



typedef struct
{

}sMtAfn09F1_ConVersion_u;  // 集中器版本信息


typedef struct
{

}sMtAfn09F1_ConVersion_f;  // 集中器版本信息





typedef struct
{


}sMtAfn09F4_ConParaCfg_u; // 集中器支持的参数配置


typedef struct
{


}sMtAfn09F4_ConParaCfg_f; // 集中器支持的参数配置



typedef struct
{


}sMtAfn09F5_ConCtrlCfg_u; // 集中器支持的控制配置    CMD_AFN_9_FN_5_SUPPORT_CTRL_CFG


typedef struct
{


}sMtAfn09F5_ConCtrlCfg_f; // 集中器支持的控制配置




typedef struct
{


}sMtAfn09F6_ConAsk1Cfg_u; // 集中器支持的1类数据配置 CMD_AFN_9_FN_6_SUPPORT_ASK1_CFG


typedef struct
{


}sMtAfn09F6_ConAsk1Cfg_f; // 集中器支持的1类数据配置



typedef struct
{


}sMtAfn09F7_ConAsk2Cfg_u; // 集中器支持的1类数据配置 CMD_AFN_9_FN_7_SUPPORT_ASK2_CFG


typedef struct
{


}sMtAfn09F7_ConAsk2Cfg_f; // 集中器支持的1类数据配置



typedef struct
{


}sMtAfn09F8_ConEvntCfg_u; // 集中器支持的事件记录配置 CMD_AFN_9_FN_8_SUPPORT_EVNT_CFG


typedef struct
{


}sMtAfn09F8_ConEvntCfg_f; // 集中器支持的事件记录配置









// 数据单元结构转换函数
typedef eMtErr (*pMtTransFunc)(eMtTransDir eDir, void* pUser, void* pFrame, UINT16 *pusfLen);  // pusFLen为该数据在帧侧的长度

/*

typedef struct
{

	eMtCmd 		   eCmd;
	eMtDir         eDir;      // 该种报文能发的方向
	eMtPn 		   ePn;
	pMtTransFunc   pFunc;
	//char*  		   pstrName;
	CString        strName;
}sMtCmdInfor;     // 与单一命令字相关的信息
*/
typedef enum
{

	MT_ROLE_UNKOWN,   // 未知身份
	MT_ROLE_MASTER,   // 主站
	MT_ROLE_CONTOR,   // 集中器 或 终端

}eMtRole;


typedef struct
{
    eMtRole eRole;                  // 身份，主站或是从站
    UINT8   ucPermitDelayMinutes;   // 允许时延
    UINT8   aucPw[MT_PW_LEN];
    

}sMtProtoInit;    // 协议初始化数据结构

typedef struct
{
	UINT8  ucRegionCode[2];          // 行政区划码(BCD)  低字节在前  高字节在后
	UINT16 usTAddress;               // 终端地址  (BIN) A2  范围(1 ~ 4294967295)
	//UINT8  ucTeamAddr:1;             // 为1表示 usTerminalAddress 为组地址,A2 == 0xFFFF即广播地址, 为 0 表示单地址
	UINT8  ucMAddress;        // 主站地址	 最好不要用位域
	
}sMtfAddress; // 帧地址格式定义


typedef struct
{

	UINT8  acRegionCode[5];    // 行政区划码(BCD)  如北京 1100   
    //UINT16  usRegionCode;		 // 行政区划码(BCD)  如北京 1100  
	//UINT32 ulTAddress;           // 终端或集中器地址  (BIN) A2 范围(1 ~ 4294967295)
    UINT16 usTAddress;           // 终端或集中器地址  (BIN) A2 范围(1 ~ 65535)
	BOOL   bTeamAddr;            // 为true表示 ulTAddress 为组地址， 为 false 表示ulTAddress单地址
	UINT8  ucMAddress;           // 主站地址	范围(0~127)

}sMtuAddress;

typedef struct
{

	BOOL     bTpv;     // 表示帧中有没有 时间标签 Tp
	BOOL     bCon;     // 是否需要确认
	eMtFmPos ePos;     // 位置
	UINT8    ucSEQ;    // SEQ = PFC & 0x0F
}sMtuSEQ;

typedef struct
{

	UINT8 SEQ:4;
	UINT8 CON:1;
	UINT8 FIN:1;
	UINT8 FIR:1;
	UINT8 TpV:1;
}sMtfSEQ;

typedef struct
{
    UINT8 ucPFC;                 // 启动帧帧序号计数器PFC
    UINT8 ucPermitDelayMinutes;  // 允许发送传输延时时间
    UINT8 ucDD;                  // 日
    UINT8 ucHH;                  // 时
    UINT8 ucmm;                  // 分
    UINT8 ucss;                  // 秒
}sMtuTp;                         // 时间标签格式TP 用户侧数据结构


typedef struct
{
     UINT8    ucPFC;                 // 启动帧帧序号计数器PFC
     sMtFmt16 sTime;                 // 启动帧发送时标
     UINT8    ucPermitDelayMinutes;  // 允许发送传输延时时间
}sMtfTp;     // 帧侧时间标签格式TP数据结构


/*
+------+------+-------+------+------+------+------+------+
|  D7  |  D6  |  D5   |  D4  |  D3  |  D2  |  D1  |  D0  |
+------+------+-------+------+------+------+------+------+
|  DIR | PRM  |FCB/ACD|  FCV |  
+------+------+-------+------+------+------+
*/

typedef enum
{

    MT_PRM_UNKWON,    // 未知方向
	MT_PRM_ACTIVE,    // 该帧来自于主动站
	MT_PRM_PASIVE,    // 该帧来自于从动站

}eMtPRM;      // 控制域中PRM字段描述 

typedef enum
{
    FCD_PRM_1_RESET     = 1,        // 复位命令
    FCD_PRM_1_USER      = 4,        // 用户数据
    FCD_PRM_1_LINK      = 9,        // 链路测试
    FCD_PRM_1_ASK_1     = 10,       // 请求1级数据
    FCD_PRM_1_ASK_2     = 11,       // 请求2级数据

}eFcodePrm1; // 上行报文控制域功能码

typedef enum
{
    FCD_PRM_0_OK        = 0,        // 认可
    FCD_PRM_0_USER      = 8,        // 用户数据
    FCD_PRM_0_NONE      = 9,        // 否认:无所召唤的数据
    FCD_PRM_0_LINK      = 11,       // 链路状态

}eFcodePrm0; // 下行报文控制域功能码

typedef struct
{
    BOOL             bAcd;       // 要求访问位
   
}sMtuCtrlUp;  // 上行控制域特有信息结构

typedef struct
{    
    BOOL           bFcv;       // 帧计数有效位FCV
    UINT8          btFCB:1;    // 帧计数位
    UINT8          btRcv:7;    // 保留不用   
}sMtuCtrlDown; // 下行控制域特有信息结构

typedef struct
{

	eMtDir eDir;       // 0 表示下行报文  1 表示上行
	eMtPRM ePRM;       // 标志该报文是来自启动站 还是从动站

    union
	{
       sMtuCtrlUp sUp;          // 上行
       sMtuCtrlDown sDown;      // 下行
    }uDir;

    union
    {
        eFcodePrm0 eFcdPrm0;   // 从动站
        eFcodePrm1 eFcdPrm1;   // 主动站
    }uFCode;  // 功能码
    	
}sMtuCtrl;   //控制域用户侧数据结构 

typedef struct
{
    sMtuAddress suAddr;          // 地址信息
    sMtuCtrl    suCtrl;
    sMtuSEQ     suSEQ;         
    
    UINT8       *pSeq2Cs;        // 从SEQ 到 CS 之间的数据
    UINT16      usSeq2CsLen;     // 从SEQ 到 CS 之间的数据的长度
}sMtPackCommon;


typedef struct
{

	UINT8       f68;          // 1
	UINT8       p10:2;        // 本协议标识  1 1
	UINT8       L1 :6;        // 2
	UINT8       L2;           // 3
	UINT8       s68;          // 4
	UINT8       C;            // 5
	sMtfAddress A;            // 6 (+7) ~ 12
	UINT8       AFN;          // 13
	UINT8       SEQ;          // 14

}sMtfComHead;                // 帧侧公共的头结构



typedef struct
{
    // 必选的
    sMtuAddress  suAddress;          // 地址信息
    eMtCmd eCmd;                     // 命令字
    UINT16 usPn;                     // 信息点元数据 (0 ~ 2033)
    UINT8  ucPFC;                    // 启动帧计数器 每对启动站和从动站之间都各维护一个独立的该计数器

    // 可选的
    union
    {
        sMtAfn04F1_ConUpPortPara_u sMtAfn04F1_TmUpPortPara; // 仅对应命令 CMD_AFN_4_FN_1_TM_UP_CFG 
      
    }uData;

}sMtuPack;   // 封装帧参数


typedef struct
{
     // 必选的
    sMtuAddress  suAddress;          // 地址信息
    eMtCmd eCmd;                     // 命令字
    UINT16 usPn;                     // 信息点元数据 (0 ~ 2033)
    // UINT8  ucPFC;                 // 启动帧计数器 每对启动站和从动站之间都各维护一个独立的该计数器

    UINT8    ucSEQ;   
    eMtFmPos ePos;     // 位置
    // 协议层数据
    sMtuCtrl    suCtrl;

    // 附加数据字段域有效性
    BOOL bEC;
    BOOL bPW;
    BOOL bTP;
	BOOL bCon;     // 是否需要确认
	

    // 附加数据
    sMtEC  sEC;         // 事件计数器
    sMtuTp sTP;         // tp字段
    UINT8  aucPW[16];   // pw字段

    // 应用层数据
    union
    {
        sMtAfn04F1_ConUpPortPara_u sMtAfn04F1_TmUpPortPara; // 仅对应命令 CMD_AFN_4_FN_1_TM_UP_CFG 

    }uData;
     
}sMtuUnpack; // 解封装数据结构



typedef struct
{
    eMtCmd eSubCmd;     // 子命令字
    UINT16 usPN;        // 子命令字一级参数
    UINT16 usLen;       // 该子命令对应应用层数据的长度, 对于同一个子命令字。应用层数据时有时无
    union
    {
		
        sMtAfn04F1_ConUpPortPara_u          sAfn04F1_ConUpPortPara; 
        sMtAfn04F2_ConUpPortParaWireless_u  sAfn04F2_ConUpPortParaWireless;
        sMtAfn04F3_MasterIpPort_u           sAfn04F3_MasterIpPort;
        sMtAfn05F1_RemoteCtrlTrip_u         sAfn05F1_RemoteCtrlTrip;
        sMtAfn05F31_TimeTick_u              sAfn05F31_TimeTick;
        sMtAfn06F1_IdAuthQ_u                sAfn06F1_IdAuthQ;
        sMtAfn06F2_IdAuthA_u                sAfn06F2_IdAuthA;
        sMtAfn06F3_RandQ_u                  sAfn06F3_RandQ;
        sMtAfn06F4_RandA_u                  sAfn06F4_RandA;
        sMtOnebyOne                         sAfn00F3_OneByOne;
     
		
		//
		sMtCfgNotElec                       sCfgNotElec;
		sMtNotElec                          sNotElec;
    }uAppData;// 应用层数据 联合

}smtSub; // 子命令及应用层数据


typedef struct
{
    /* 必选域 */
    sMtuAddress  sAddress;               // 地址信息
    eMtAFN       eMainCmd;               // 主命令字
	
	// 控制域
    sMtuCtrl     sCtrl;                  // 控制域   方向等信息
    eMtFmPos     ePos;                   // 位置   打包时将忽略该参数
    UINT8        ucSEQ;                  // SEQ字段 是 P/RSEQ  范围(0~15)
    BOOL         bCon;                   // 是否需要确认	

    // 附加域
    BOOL bEC;
    BOOL bPW;
    BOOL bTP;

    sMtEC  sEC;                         // 事件计数器
    sMtuTp sTP;                         // tp字段
    UINT8  aucPW[17];                   // pw字段

    /* 变长域 */
    UINT8    ucSubNum;                  // 该帧中包含子命令字的个数最大值(255)
	smtSub   sSub[1];                   // 子命令类型及应用层数据 变长

}smtPack;       // 用户侧封装解和封装数据结构















// 转换函数在这里声明
// 用户侧数据结构到帧侧数据结构转换





eMtErr emt_trans_Afn04F1_ConUpPortPara(eMtTransDir eDir,
                                      void  *pUser,
                                      void  *pFrame,
                                      UINT16 *pusfLen);


eMtErr emt_trans_Afn04F2_ConUpPortParaWireless(eMtTransDir eDir,
                                              void  *pUser,
                                              void  *pFrame,
                                              UINT16 *pusfLen);


eMtErr emt_trans_Afn04F3_MasterIpPort(eMtTransDir eDir,
                                      void  *pUser,
                                      void  *pFrame,
                                      UINT16 *pusfLen);



eMtErr emt_trans_Afn04F4_MstSmsPhone(eMtTransDir eDir,
                                        void  *psUser,
                                        void  *psFrame,
                                        UINT16 *pusfLen);



eMtErr emt_trans_Afn04F5_UpMsgAuth(eMtTransDir eDir,
                                   void  *psUser,
                                   void  *psFrame,
                                   UINT16 *pusfLen);


eMtErr emt_trans_Afn04f6_ConGroupAddr(eMtTransDir eDir,
                                      void  *psUser,
                                      void  *psFrame,
                                      UINT16 *pusfLen);

// 集中器ip地址参数设置数据结构转换函数
eMtErr emt_trans_Afn04F7_ConIpPort(eMtTransDir eDir,
                                   void  *psUser,
                                   void  *psFrame,
                                   UINT16 *pusfLen);

// 集中器上行通信工作方式（以太专网或虚拟专网）
eMtErr emt_trans_Afn04F8_ConUpComWay(eMtTransDir eDir,
                                    void  *psUser,
                                    void  *psFrame,
                                    UINT16 *pusfLen);


// 集中器与终端通信读取数据运行参数设置 数据结构转换函数
eMtErr emt_trans_Afn04F9_Con2TmlComPara(eMtTransDir eDir,
                                        void  *psUser,
                                        void  *psFrame,
                                        UINT16 *pusfLen);




eMtErr emt_trans_Afn04F10_ConDownPara(eMtTransDir eDir,
                                      void  *psUser,
                                      void  *psFrame,
                                       UINT16 *pusfLen);



eMtErr emt_trans_Afn04F11_VpnPwd(eMtTransDir eDir,
                                 void  *psUser,
                                 void  *psFrame,
                                 UINT16 *pusfLen);



eMtErr emt_trans_Afn04F12_ConUpLimit(eMtTransDir eDir,
                                     void  *psUser,
                                     void  *psFrame,
                                     UINT16 *pusfLen);






eMtErr emt_trans_Afn05F1_RemoteCtrlTrip(eMtTransDir eDir,
                                        void  *psUser,
                                        void  *psFrame,
                                        UINT16 *pusfLen);



eMtErr emt_trans_Afn05F31_TimeTick(eMtTransDir eDir,
                                   void  *psUser,
                                   void  *psFrame,
                                   UINT16 *pusfLen);


eMtErr emt_trans_Afn05F49_PortSuspend(eMtTransDir eDir,
                                      void  *psUser,
                                      void  *psFrame,
                                      UINT16 *pusfLen);


eMtErr emt_trans_Afn05F50_PortResume(eMtTransDir eDir,
                                     void  *psUser,
                                     void  *psFrame,
                                     UINT16 *pusfLen);


eMtErr emt_trans_Afn05F51_PortAgain(eMtTransDir eDir,
                                    void  *psUser,
                                    void  *psFrame,
                                    UINT16 *pusfLen);




// 身份认证请求数据结构转换函数
eMtErr emt_trans_Afn06F1_IdAuthQ(eMtTransDir eDir,
                                 void  *psUser,
                                 void  *psFrame,
                                 UINT16 *pusfLen);

eMtErr emt_trans_Afn06F2_IdAuthA(eMtTransDir eDir,
                                 void  *psUser,
                                 void  *psFrame,
                                 UINT16 *pusfLen);



eMtErr emt_trans_Afn06F3_RandQ(eMtTransDir eDir,
                               void  *psUser,
                               void  *psFrame,
                               UINT16 *pusfLen);

eMtErr emt_trans_Afn06F4_RandA(eMtTransDir eDir,
                               void  *psUser,
                               void  *psFrame,
                               UINT16 *pusfLen);



eMtErr emt_trans_Afn09F1_ConVersion(eMtTransDir eDir,
                                    void  *psUser,
                                    void  *psFrame,
                                    UINT16 *pusfLen);




eMtErr emt_trans_Afn09F4_ConParaCfg(eMtTransDir eDir,
                                    void *psUser,
                                    void  *psFrame,
                                    UINT16 *pusfLen);


eMtErr emt_trans_Afn09F5_ConCtrlCfg(eMtTransDir eDir,
                                    void *psUser,
                                    void  *psFrame,
                                    UINT16 *pusfLen);





eMtErr emt_trans_Afn09F6_ConAsk1Cfg(eMtTransDir eDir,
                                    void *psUser,
                                    void  *psFrame,
                                    UINT16 *pusfLen);




eMtErr emt_trans_Afn09F7_ConAsk2Cfg(eMtTransDir eDir,
                                    void *psUser,
                                    void  *psFrame,
                                    UINT16 *pusfLen);




eMtErr emt_trans_Afn09F8_ConEvntCfg(eMtTransDir eDir,
                                    void *psUser,
                                    void  *psFrame,
                                    UINT16 *pusfLen);











#endif
#pragma pack(pop)  // 一字节对齐

#endif // _NX_RULER_TYPES_H_