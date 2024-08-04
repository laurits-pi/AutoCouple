#ifndef _INTERACT_H
#define _INTERACT_H

#ifndef _MSC_VER
#define WINAPI __stdcall
#endif

#ifdef __cplusplus
extern "C" {
#endif

enum FUNCITEM
{
//	TYPE0=0,			//属性设置
//	SET_UNIT_FLAG,
	AUTO_SET=0,
	INIT_BOARD,
	SET_OUTMODE,
	SET_HOME_MODE,
	SET_DIR,
	ENABLE_EL,
	ENABLE_ORG,
	ENABLE_ALM,
	SET_EL_LOGIC,
	SET_ORG_LOGIC,
	SET_ALM_LOGIC,
	
	ENABLE_CARD_ALM,
	SET_CARD_ALM_LOGIC,

//	TYPE1,				//参数设置
	SET_MAXSPEED,
	SET_CONSPEED,
	SET_PROFILE,
	SET_VECTOR_CONSPEED,
	SET_VECTOR_PROFILE,
	SET_S_CURVE,
	SET_S_SECTION,
	SET_ABS_POS,
	RESET_POS,
//	SET_UNIT,
//	TYPE2,				//运动指令
	CON_PMOVE,
	CON_PMOVE2,
	CON_PMOVE3,
	CON_PMOVE4,
//	CON_PMOVE_TO,
	FAST_PMOVE,
	FAST_PMOVE2,
	FAST_PMOVE3,
	FAST_PMOVE4,
//	FAST_PMOVE_TO,
	CON_VMOVE,
	CON_VMOVE2,
	CON_VMOVE3,
	CON_VMOVE4,
	FAST_VMOVE,
	FAST_VMOVE2,
	FAST_VMOVE3,
	FAST_VMOVE4,
	CON_HMOVE,
	CON_HMOVE2,
	CON_HMOVE3,
	CON_HMOVE4,
	FAST_HMOVE,
	FAST_HMOVE2,
	FAST_HMOVE3,
	FAST_HMOVE4,
	CON_LINE2,
	CON_LINE3,
	CON_LINE4,
	FAST_LINE2,
	FAST_LINE3,
	FAST_LINE4,

//	TYPE3,				//停止指令
	SUDDEN_STOP,
	SUDDEN_STOP2,
	SUDDEN_STOP3,
	SUDDEN_STOP4,
	DECEL_STOP,
	DECEL_STOP2,
	DECEL_STOP3,
	DECEL_STOP4,
	MOVE_PAUSE,
	MOVE_RESUME,
//	TYPE4,				//IO指令
	CHECKIN_BYTE,
	CHECKIN_BIT,
	OUTPORT_BIT,
	OUTPORT_BYTE,
	CHECK_SFR,
	CHECK_SFR_BIT,
//	TYPE5,				//特殊功能
	SET_BACKLASH,
	START_BACKLASH,
	END_BACKLASH,
	CHANGE_POS,
//	TYPE6,				//查询函数
	GET_MAX_AXE,
	GET_BOARD_NUM,
	GET_AXE,
//	GET_UNIT,
	CHECK_IC,
	GET_ABS_POS,
	ENABLE_SOFTLIMIT,
	SET_SOFTLIMIT,
	SET_SOFTLIMIT_DATA,
	CHECK_SOFTLIMIT,

	GET_CONSPEED,
	GET_VECTOR_CONSPEED,
	GET_PROFILE,
	GET_VECTOR_PROFILE,
	GET_RATE,
	GET_CUR_DIR,
	CHECK_STATUS,
	CHECK_DONE,
	CHECK_LIMIT,
	CHECK_HOME,
	CHECK_ALARM,
                CHECK_CARD_ALARM,
	
	GET_ERR,
	GET_LAST_ERR,
	RESET_ERR,
	GET_LIB_VER,
	GET_SYS_VER,
	GET_CARD_VER,

	WRITE_PASSWORD_FLASH,
                READ_PASSWORD_FLASH,
	CLEAR_PASSWORD_FLASH,
	WRITE_FLASH,
                READ_FLASH,
	CLEAR_FLASH,

};
/////////////////////////////////////////////////////
//控制卡初始化函数
int WINAPI auto_set(void);
int WINAPI init_board(void);
/////////////////////////////////////////////////////

//轴属性设置函数
int WINAPI set_outmode(int ch,int mode,int logic);
int WINAPI set_home_mode(int ch,int origin_mode);
int WINAPI set_dir(int ch,int dir);
int WINAPI enable_el(int ch,int flag);//flag--1,有效;flag--0,无效
int WINAPI enable_org(int ch,int flag);//mode--1,有效;flag--0,无效
int WINAPI enable_alm(int ch , int flag);//flag--1,有效;flag--0,无效
int WINAPI set_el_logic(int ch,int mode);//mode--0,低电平有效;mode--1,高电平有效
int WINAPI set_org_logic(int ch,int mode);//mode--0,低电平有效;mode--1,高电平有效
int WINAPI set_alm_logic(int ch ,int mode);//mode--0,低电平有效;mode--1,高电平有效

//板卡报警信号相关设置和查询
int WINAPI enable_card_alm(int cardno , int flag);//flag--1,有效;flag--0,无效
int WINAPI set_card_alm_logic(int cardno ,int mode);//mode--0,低电平有效;mode--1,高电平有效
int WINAPI check_card_alarm(int cardno);

//参数设置函数
int WINAPI set_maxspeed(int ch , double speed);
int WINAPI set_conspeed(int ch , double conspeed);
int WINAPI set_vector_conspeed(double conspeed);
int WINAPI set_profile(int ch , double vl , double vh , double ad, double dc);
int WINAPI set_vector_profile(double vec_vl , double vec_vh ,double vec_ad,double vec_dc);
int WINAPI set_s_section(int ch,double accel_sec,double decel_sec);
int WINAPI set_s_curve(int ch,int mode);

int WINAPI set_abs_pos(int ch,double pos);
int WINAPI reset_pos(int ch);

///////////////////////////////////////////////////////////////
//运动指令函数
int WINAPI con_pmove(int ch,double step);
int WINAPI con_pmove2(int ch1,double step1,int ch2,double step2);
int WINAPI con_pmove3(int ch1,double step1,int ch2,double step2,int ch3,double step3);
int WINAPI con_pmove4(int ch1,double step1,int ch2,double step2,int ch3,double step3,int ch4,double step4);
int WINAPI con_pmove_to(int ch, double step);

int WINAPI fast_pmove(int ch,double step);
int WINAPI fast_pmove2(int ch1,double step1,int ch2,double step2);
int WINAPI fast_pmove3(int ch1,double step1,int ch2,double step2,int ch3,double step3);
int WINAPI fast_pmove4(int ch1,double step1,int ch2,double step2,int ch3,double step3,int ch4,double step4);
int WINAPI fast_pmove_to(int ch, double step);

int WINAPI con_vmove(int ch,int dir);
int WINAPI con_vmove2(int ch1,int dir1,int ch2,int dir2);
int WINAPI con_vmove3(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3);
int WINAPI con_vmove4(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3,int ch4,int dir4);

int WINAPI fast_vmove(int ch,int dir);
int WINAPI fast_vmove2(int ch1,int dir1,int ch2,int dir2);
int WINAPI fast_vmove3(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3);
int WINAPI fast_vmove4(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3,int ch4,int dir4);

int WINAPI con_hmove(int ch ,int dir1);
int WINAPI con_hmove2(int ch1,int dir1,int ch2,int dir2);
int WINAPI con_hmove3(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3);
int WINAPI con_hmove4(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3,int ch4,int dir4);

int WINAPI fast_hmove(int ch,int dir);
int WINAPI fast_hmove2(int ch1,int dir1,int ch2,int dir2);
int WINAPI fast_hmove3(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3);
int WINAPI fast_hmove4(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3,int ch4,int dir4);

int WINAPI con_line2(int ch1,double step1,int ch2, double step2);
int WINAPI con_line3(int ch1,double step1,int ch2,double step2,int ch3,double step3);
int WINAPI con_line4(int ch1,double step1,int ch2,double step2,int ch3,double step3,int ch4,double step4);

int WINAPI fast_line2(int ch1,double step1,int ch2,double step2);
int WINAPI fast_line3(int ch1,double step1,int ch2,double step2,int ch3,double step3);
int WINAPI fast_line4(int ch1,double step1,int ch2,double step2,int ch3,double step3,int ch4,double step4);

///////////////////////////////////////////////////////////////
//制动函数
int WINAPI sudden_stop(int ch);
int WINAPI sudden_stop2(int ch1,int ch2);
int WINAPI sudden_stop3(int ch1,int ch2,int ch3);
int WINAPI sudden_stop4(int ch1,int ch2,int ch3,int ch4);

int WINAPI decel_stop(int ch);
int WINAPI decel_stop2(int ch1,int ch2);
int WINAPI decel_stop3(int ch1,int ch2,int ch3);
int WINAPI decel_stop4(int ch1,int ch2,int ch3,int ch4);

int WINAPI move_pause(int ch);
int WINAPI move_resume(int ch);


///////////////////////////////////////////////////////////////
//I/O口操作函数
int WINAPI checkin_byte(int cardno);
int WINAPI checkin_bit(int cardno,int bitno);
int WINAPI outport_bit(int cardno,int bitno,int status);
int WINAPI outport_byte(int cardno,int data);
int WINAPI check_sfr(int cardno);
int WINAPI check_sfr_bit(int cardno,int bitno);

//特殊功能
int WINAPI set_backlash(int ch,double blash);
int WINAPI start_backlash(int ch);
int WINAPI end_backlash(int ch);
int WINAPI change_pos(int ch, double pos);

int WINAPI enable_softlimit(int ch, int mode);
int WINAPI set_softlimit(int ch, int source, int action);
int WINAPI set_softlimit_data(int ch, double nel, double pel);
int WINAPI check_softlimit(int ch);
///////////////////////////////////////////////////////////////
//位置和状态查询函数
int WINAPI get_max_axe();
int WINAPI get_board_num();
int WINAPI get_axe(int cardno);

int WINAPI check_IC(int cardno);
int WINAPI get_abs_pos(int ch,double *pos);
long WINAPI get_cur_dir(int ch);

double WINAPI get_conspeed(int ch);
double WINAPI get_vector_conspeed();
int    WINAPI get_profile(int ch,double *vl,double *vh,double *ad,double *dc);

int    WINAPI get_vector_profile(double *vec_vl,double *vec_vh,double *vec_ad,double *vec_dc);
double WINAPI get_rate(int ch);

int    WINAPI check_status(int ch);
int    WINAPI check_done(int ch);
int    WINAPI check_limit(int ch);
int    WINAPI check_home(int ch);
int    WINAPI check_alarm(int ch);

///////////////////////////////////////////////////////////////
//SPI存储芯片操作函数
int write_password_flash(int cardno, int no, long data,long password);  //写SPI存储芯片密码区某个地址
int read_password_flash(int cardno, int no, long *data,long password);  //校验SPI存储芯片密码
int clear_password_flash(int cardno, long password); //擦除SPI存储芯片密码区

int write_flash(int cardno,int piece, int no, long data);  //写SPI存储芯片除密码区外的某个地址
int read_flash(int cardno,int piece,int no,long *data );  //读SPI存储芯片除密码区外的某个地址
int clear_flash(int cardno, int piece); //擦除SPI存储芯片除密码区外的某片地址

//错误代码操作函数
int WINAPI get_last_err();
int WINAPI get_err(int index,int *data);
int WINAPI reset_err();

//版本读取函数
int WINAPI get_lib_ver(long* major,long *minor1,long *minor2);
int WINAPI get_sys_ver(long* major,long *minor1,long *minor2);
int WINAPI get_card_ver(int cardno,long* type,long* major,long *minor1,long *minor2);

int WINAPI GetDllInfo(int InfoNum,long * plRtn);

/////////////////////////////////////////////////////
//调试使用
int WINAPI write_reg(int ch,int reg,long data);
int WINAPI read_reg(int ch,int reg,long *data);
int WINAPI write_card_reg(int cardno, int addr,long data);
int WINAPI read_card_reg(int cardno, int addr,long* data);
//错误代码测试处理
int WINAPI get_debug_ivar(int index,int *data);
int WINAPI get_debug_dbvar(int index,double *data);
int WINAPI get_sys_var(int index,int *data);

#ifdef __cplusplus
}
#endif

#endif
