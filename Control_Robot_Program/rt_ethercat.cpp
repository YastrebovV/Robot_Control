#include "rt_ethercat.h"
//#include "staticVar.h"

RT_TASK ec_task;
RT_TASK mt_task;
RT_TASK mt_2_task;
RT_TASK mt_3_task;
RT_TASK mt_4_task;
RT_TASK mt_5_task;
RT_TASK mt_6_task;

static int run = 1;

bool rt_ethercat::enable_mt_ex_Arr[6];
bool rt_ethercat::dir_mt_ex_Arr[6];
bool rt_ethercat::start_ex_Arr[6];
int rt_ethercat::steps_ex_Arr[6];
bool rt_ethercat::pul_mt_ex_Arr[6];
unsigned long long rt_ethercat::speed_axis_move = 1500000;
unsigned int rt_ethercat::acc_axis_move[6];
unsigned int rt_ethercat::absolutePos[6];
bool rt_ethercat::startAxisMastering = false;
bool rt_ethercat::masteringStarted = false;

char byte1= 0x00;
char byte2 = 0x00;
char byte3 = 0x00;
char byte4 = 0x00;

/****************************************************************************/
// EtherCAT

static ec_master_t *master = NULL;
static ec_master_state_t master_state = {};

static ec_domain_t *domainPdo = NULL;
static ec_domain_state_t domain_pdo_state = {};

//static ec_domain_t *domainPdoEK = NULL;
//static ec_domain_state_t domain_pdo_stateEK = {};

static uint8_t *domain_pd = NULL;
//static uint8_t *domain_pd_EK = NULL;

static ec_slave_config_t *sc_dig_out_AX_01 = NULL;

static ec_slave_config_t *sc_dig_in_01 = NULL;
static ec_slave_config_t *sc_dig_in_02 = NULL;
static ec_slave_config_t *sc_dig_out_01 = NULL;
static ec_slave_config_t *sc_dig_out_02 = NULL;


/****************************************************************************/
// process data

#define DigOutSlaveAX01_Pos 1001, 0

#define BusCoupler01_Pos  1002, 0
#define DigInSlave01_Pos 1002, 1
#define DigInSlave02_Pos 1002, 2
#define DigOutSlave01_Pos 1002, 3
#define DigOutSlave02_Pos 1002, 4

#define Beckhoff_EK1100 0x00000002, 0x044c2c52
#define Beckhoff_EL1014 0x00000002, 0x03f63052
#define Beckhoff_EL1018 0x00000002, 0x03fa3052
#define Beckhoff_EL2004 0x00000002, 0x07d43052
#define Beckhoff_EL2008 0x00000002, 0x07d83052

#define AX58100 0x00000b95, 0x00010202

// offsets for PDO entries AX58100
static unsigned int off_dig_outAX[4], bo_dig_outAX[4];

// offsets for PDO entries
static unsigned int off_dig_in[12], bo_dig_in[12];
static unsigned int off_dig_out[16], bo_dig_out[16];


// process data
//const static ec_pdo_entry_reg_t domain_pdo_regsAX[] = {
//   {DigOutSlaveAX01_Pos, AX58100, 0x3101, 0x01, &off_dig_outAX[0], &bo_dig_outAX[0]},
//   {DigOutSlaveAX01_Pos, AX58100, 0x3101, 0x02, &off_dig_outAX[1], &bo_dig_outAX[1]},
//   {DigOutSlaveAX01_Pos, AX58100, 0x3101, 0x03, &off_dig_outAX[2], &bo_dig_outAX[2]},
//   {DigOutSlaveAX01_Pos, AX58100, 0x3101, 0x04, &off_dig_outAX[3], &bo_dig_outAX[3]},
//   {}
//};

const static ec_pdo_entry_reg_t domain_pdo_regs[] = {
   {DigOutSlaveAX01_Pos, AX58100, 0x3101, 0x01, &off_dig_outAX[0], &bo_dig_outAX[0]},
   {DigOutSlaveAX01_Pos, AX58100, 0x3101, 0x02, &off_dig_outAX[1], &bo_dig_outAX[1]},
   {DigOutSlaveAX01_Pos, AX58100, 0x3101, 0x03, &off_dig_outAX[2], &bo_dig_outAX[2]},
   {DigOutSlaveAX01_Pos, AX58100, 0x3101, 0x04, &off_dig_outAX[3], &bo_dig_outAX[3]},
   {DigInSlave01_Pos, Beckhoff_EL1014, 0x6000, 0x01, &off_dig_in[0], &bo_dig_in[0]},
   {DigInSlave01_Pos, Beckhoff_EL1014, 0x6010, 0x01, &off_dig_in[1], &bo_dig_in[1]},
   {DigInSlave01_Pos, Beckhoff_EL1014, 0x6020, 0x01, &off_dig_in[2], &bo_dig_in[2]},
   {DigInSlave01_Pos, Beckhoff_EL1014, 0x6030, 0x01, &off_dig_in[3], &bo_dig_in[3]},
   {DigInSlave02_Pos, Beckhoff_EL1018, 0x6000, 0x01, &off_dig_in[4], &bo_dig_in[4]},
   {DigInSlave02_Pos, Beckhoff_EL1018, 0x6010, 0x01, &off_dig_in[5], &bo_dig_in[5]},
   {DigInSlave02_Pos, Beckhoff_EL1018, 0x6020, 0x01, &off_dig_in[6], &bo_dig_in[6]},
   {DigInSlave02_Pos, Beckhoff_EL1018, 0x6030, 0x01, &off_dig_in[7], &bo_dig_in[7]},
   {DigInSlave02_Pos, Beckhoff_EL1018, 0x6040, 0x01, &off_dig_in[8], &bo_dig_in[8]},
   {DigInSlave02_Pos, Beckhoff_EL1018, 0x6050, 0x01, &off_dig_in[9], &bo_dig_in[9]},
   {DigInSlave02_Pos, Beckhoff_EL1018, 0x6060, 0x01, &off_dig_in[10], &bo_dig_in[10]},
   {DigInSlave02_Pos, Beckhoff_EL1018, 0x6070, 0x01, &off_dig_in[11], &bo_dig_in[11]},
   {DigOutSlave01_Pos, Beckhoff_EL2004, 0x7000, 0x01, &off_dig_out[4], &bo_dig_out[4]},
   {DigOutSlave01_Pos, Beckhoff_EL2004, 0x7010, 0x01, &off_dig_out[5], &bo_dig_out[5]},
   {DigOutSlave01_Pos, Beckhoff_EL2004, 0x7020, 0x01, &off_dig_out[6], &bo_dig_out[6]},
   {DigOutSlave01_Pos, Beckhoff_EL2004, 0x7030, 0x01, &off_dig_out[7], &bo_dig_out[7]},
   {DigOutSlave02_Pos, Beckhoff_EL2008, 0x7000, 0x01, &off_dig_out[8], &bo_dig_out[8]},
   {DigOutSlave02_Pos, Beckhoff_EL2008, 0x7010, 0x01, &off_dig_out[9], &bo_dig_out[9]},
   {DigOutSlave02_Pos, Beckhoff_EL2008, 0x7020, 0x01, &off_dig_out[10], &bo_dig_out[10]},
   {DigOutSlave02_Pos, Beckhoff_EL2008, 0x7030, 0x01, &off_dig_out[11], &bo_dig_out[11]},
   {DigOutSlave02_Pos, Beckhoff_EL2008, 0x7040, 0x01, &off_dig_out[12], &bo_dig_out[12]},
   {DigOutSlave02_Pos, Beckhoff_EL2008, 0x7050, 0x01, &off_dig_out[13], &bo_dig_out[13]},
   {DigOutSlave02_Pos, Beckhoff_EL2008, 0x7060, 0x01, &off_dig_out[14], &bo_dig_out[14]},
   {DigOutSlave02_Pos, Beckhoff_EL2008, 0x7070, 0x01, &off_dig_out[15], &bo_dig_out[15]},
   {}
};

/* Slave 2, "AX58100"
 * Vendor ID:       0x00000b95
 * Product code:    0x00010202
 * Revision number: 0x00000001
 */

ec_pdo_entry_info_t slave_pdo_entries[] = {
   {0x3101, 0x01, 8}, /* Output */
   {0x3101, 0x02, 8}, /* Output */
   {0x3101, 0x03, 8}, /* Output */
   {0x3101, 0x04, 8}, /* Output */
};

ec_pdo_info_t slave_pdos[] = {
   {0x1a00, 1, slave_pdo_entries + 0}, /* Channel 1 */
   {0x1a01, 1, slave_pdo_entries + 1}, /* Channel 2 */
   {0x1a02, 1, slave_pdo_entries + 2}, /* Channel 3 */
   {0x1a03, 1, slave_pdo_entries + 3}, /* Channel 4 */
};

ec_sync_info_t slave_syncs[] = {
  {0, EC_DIR_OUTPUT, 1, slave_pdos + 0, EC_WD_ENABLE},
  {1, EC_DIR_OUTPUT, 1, slave_pdos + 1, EC_WD_ENABLE},
  {2, EC_DIR_OUTPUT, 1, slave_pdos + 2, EC_WD_ENABLE},
  {3, EC_DIR_OUTPUT, 1, slave_pdos + 3, EC_WD_ENABLE},
  {0xff}
};

/****************************************************************************/
/* Slave 1, "EL1014"
 * Vendor ID:       0x00000002
 * Product code:    0x03f63052
 * Revision number: 0x00100000
 */

ec_pdo_entry_info_t slave_1_pdo_entries[] = {
   {0x6000, 0x01, 1}, /* Input */
   {0x6010, 0x01, 1}, /* Input */
   {0x6020, 0x01, 1}, /* Input */
   {0x6030, 0x01, 1}, /* Input */
};

ec_pdo_info_t slave_1_pdos[] = {
   {0x1a00, 1, slave_1_pdo_entries + 0}, /* Channel 1 */
   {0x1a01, 1, slave_1_pdo_entries + 1}, /* Channel 2 */
   {0x1a02, 1, slave_1_pdo_entries + 2}, /* Channel 3 */
   {0x1a03, 1, slave_1_pdo_entries + 3}, /* Channel 4 */
};

ec_sync_info_t slave_1_syncs[] = {
   {0, EC_DIR_INPUT, 4, slave_1_pdos + 0, EC_WD_ENABLE},
   {0xff}
};
/****************************************************************************/
/* Slave 1, "EL1018"
 * Vendor ID:       0x00000002
 * Product code:    0x03fa3052
 * Revision number: 0x00100000
 */

ec_pdo_entry_info_t slave_2_pdo_entries[] = {
   {0x6000, 0x01, 1}, /* Input */
   {0x6010, 0x01, 1}, /* Input */
   {0x6020, 0x01, 1}, /* Input */
   {0x6030, 0x01, 1}, /* Input */
   {0x6040, 0x01, 1}, /* Input */
   {0x6050, 0x01, 1}, /* Input */
   {0x6060, 0x01, 1}, /* Input */
   {0x6070, 0x01, 1}, /* Input */
};

ec_pdo_info_t slave_2_pdos[] = {
   {0x1a00, 1, slave_2_pdo_entries + 0}, /* Channel 1 */
   {0x1a01, 1, slave_2_pdo_entries + 1}, /* Channel 2 */
   {0x1a02, 1, slave_2_pdo_entries + 2}, /* Channel 3 */
   {0x1a03, 1, slave_2_pdo_entries + 3}, /* Channel 4 */
   {0x1a04, 1, slave_2_pdo_entries + 4}, /* Channel 5 */
   {0x1a05, 1, slave_2_pdo_entries + 5}, /* Channel 6 */
   {0x1a06, 1, slave_2_pdo_entries + 6}, /* Channel 7 */
   {0x1a07, 1, slave_2_pdo_entries + 7}, /* Channel 8 */
};

ec_sync_info_t slave_2_syncs[] = {
   {0, EC_DIR_INPUT, 8, slave_2_pdos + 0, EC_WD_ENABLE},
   {0xff}
};

/* Slave 2, "EL2004"
 * Vendor ID:       0x00000002
 * Product code:    0x07d43052
 * Revision number: 0x00100000
 */

ec_pdo_entry_info_t slave_3_pdo_entries[] = {
   {0x7000, 0x01, 1}, /* Output */
   {0x7010, 0x01, 1}, /* Output */
   {0x7020, 0x01, 1}, /* Output */
   {0x7030, 0x01, 1}, /* Output */
};

ec_pdo_info_t slave_3_pdos[] = {
   {0x1600, 1, slave_3_pdo_entries + 0}, /* Channel 1 */
   {0x1601, 1, slave_3_pdo_entries + 1}, /* Channel 2 */
   {0x1602, 1, slave_3_pdo_entries + 2}, /* Channel 3 */
   {0x1603, 1, slave_3_pdo_entries + 3}, /* Channel 4 */
};

ec_sync_info_t slave_3_syncs[] = {
   {0, EC_DIR_OUTPUT, 4, slave_3_pdos + 0, EC_WD_ENABLE},
   {0xff}
};

/* Slave 2, "EL2008"
 * Vendor ID:       0x00000002
 * Product code:    0x07d83052
 * Revision number: 0x00100000
 */

ec_pdo_entry_info_t slave_4_pdo_entries[] = {
   {0x7000, 0x01, 1}, /* Output */
   {0x7010, 0x01, 1}, /* Output */
   {0x7020, 0x01, 1}, /* Output */
   {0x7030, 0x01, 1}, /* Output */
   {0x7040, 0x01, 1}, /* Output */
   {0x7050, 0x01, 1}, /* Output */
   {0x7060, 0x01, 1}, /* Output */
    {0x7070, 0x01, 1}, /* Output */
};

ec_pdo_info_t slave_4_pdos[] = {
   {0x1600, 1, slave_4_pdo_entries + 0}, /* Channel 1 */
   {0x1601, 1, slave_4_pdo_entries + 1}, /* Channel 2 */
   {0x1602, 1, slave_4_pdo_entries + 2}, /* Channel 3 */
   {0x1603, 1, slave_4_pdo_entries + 3}, /* Channel 4 */
   {0x1604, 1, slave_4_pdo_entries + 4}, /* Channel 5 */
   {0x1605, 1, slave_4_pdo_entries + 5}, /* Channel 6 */
   {0x1606, 1, slave_4_pdo_entries + 6}, /* Channel 7 */
   {0x1607, 1, slave_4_pdo_entries + 7}, /* Channel 8 */
};

ec_sync_info_t slave_4_syncs[] = {
   {0, EC_DIR_OUTPUT, 8, slave_4_pdos + 0, EC_WD_ENABLE},
   {0xff}
};

rt_ethercat::rt_ethercat(){

}

/*****************************************************************************
 * Realtime task
 ****************************************************************************/

void rt_check_domain_state(void)
{

    ec_domain_state_t ds = {};

    ecrt_domain_state(domainPdo, &ds);

    if (ds.working_counter != domain_pdo_state.working_counter) {
        printf("Domain_PDO: WC %u.\n", ds.working_counter);
    }

    if (ds.wc_state != domain_pdo_state.wc_state) {
        printf("Domain_PDO: State %u.\n", ds.wc_state);
    }

    domain_pdo_state = ds;
}

/****************************************************************************/

void rt_check_master_state(void)
{
    ec_master_state_t ms;

    ecrt_master_state(master, &ms);

    if (ms.slaves_responding != master_state.slaves_responding) {
        printf("%u slave(s).\n", ms.slaves_responding);
    }

    if (ms.al_states != master_state.al_states) {
        printf("AL states: 0x%02X.\n", ms.al_states);
    }

    if (ms.link_up != master_state.link_up) {
        printf("Link is %s.\n", ms.link_up ? "up" : "down");
    }

    master_state = ms;
}

/****************************************************************************/

void ethercat_task(void *arg)
{
    int cycle_counter = 0;

    rt_task_set_periodic(NULL, TM_NOW, 300000); // ns

    while (run) {
        rt_task_wait_period(NULL);

        cycle_counter++;

        // receive EtherCAT frames
        ecrt_master_receive(master);
        ecrt_domain_process(domainPdo);

        rt_check_master_state();

        if (!(cycle_counter % 10)) {
           rt_check_domain_state();
        }

        if(EC_READ_BIT(domain_pd+off_dig_in[0], bo_dig_in[0]) && rt_ethercat::getStartAxMastering()){
            rt_ethercat::setStart(0, false);
            rt_ethercat::setStartAxMastering(false);
            rt_ethercat::setmasteringStarted(false);
        }
        if(rt_ethercat::getStartAxMastering() && !rt_ethercat::getmasteringStarted()){
             rt_ethercat::setmasteringStarted(true);
             rt_ethercat::setAxisSpeed(1500000);
             rt_ethercat::setDir_mt(0,true);
             rt_ethercat::setSteps(0,2880);
             rt_ethercat::setStart(0, true);
        }

//Axis 1
        if(rt_ethercat::getEnable_mt(0)){
            byte2 |= (1<<1);
        }else
        {
            byte2 &= ~(1<<1);
        }
       if(rt_ethercat::getDir_mt(0)){
            byte1 |= (1<<7);
            //EC_WRITE_BIT(domain_pd+off_dig_out[4], bo_dig_out[4], true);
        }else
        {
            byte1 &= ~(1<<7);
            //EC_WRITE_BIT(domain_pd+off_dig_out[4], bo_dig_out[4], false);
        }

        if(rt_ethercat::getPul_mt(0)){
            byte1 |= (1<<5);
        }else{
            byte1 &= ~(1<<5);
        }

//Axis 2
        if(rt_ethercat::getEnable_mt(1)){
            byte2 |= (1<<7);
        }else
        {
            byte2 &= ~(1<<7);
        }
       if(rt_ethercat::getDir_mt(1)){
            byte2 |= (1<<5);
        }else
        {
            byte2 &= ~(1<<5);
        }

        if(rt_ethercat::getPul_mt(1)){
            byte2 |= (1<<3);
        }else{
            byte2 &= ~(1<<3);
        }
//Axis 3
        if(rt_ethercat::getEnable_mt(2)){
            byte2 |= (1<<0);
        }else
        {
            byte2 &= ~(1<<0);
        }
        if(rt_ethercat::getDir_mt(2)){
            byte1 |= (1<<6);
        }else
        {
            byte1 &= ~(1<<6);
        }

        if(rt_ethercat::getPul_mt(2)){
            byte1 |= (1<<4);
        }else{
            byte1 &= ~(1<<4);
        }

//Axis 4
        if(rt_ethercat::getEnable_mt(3)){
            byte4 |= (1<<0);
        }else
        {
            byte4 &= ~(1<<0);
        }
        if(rt_ethercat::getDir_mt(3)){
            byte3 |= (1<<6);
        }else
        {
            byte3 &= ~(1<<6);
        }

        if(rt_ethercat::getPul_mt(3)){
            byte3 |= (1<<4);
        }else{
            byte3 &= ~(1<<4);
        }

//Axis 5
        if(rt_ethercat::getEnable_mt(4)){
            byte2 |= (1<<6);
        }else
        {
            byte2 &= ~(1<<6);
        }
        if(rt_ethercat::getDir_mt(4)){
            byte2 |= (1<<4);
        }else
        {
            byte2 &= ~(1<<4);
        }

        if(rt_ethercat::getPul_mt(4)){
            byte2 |= (1<<2);
        }else{
            byte2 &= ~(1<<2);
        }
//Axis 6
        if(rt_ethercat::getEnable_mt(5)){
            byte4 |= (1<<6);
        }else
        {
            byte4 &= ~(1<<6);
        }
        if(rt_ethercat::getDir_mt(5)){
            byte4 |= (1<<4);
        }else
        {
            byte4 &= ~(1<<4);
        }

        if(rt_ethercat::getPul_mt(5)){
            byte4 |= (1<<2);
        }else{
            byte4 &= ~(1<<2);
        }
        EC_WRITE_U8(domain_pd + off_dig_outAX[0], byte1);
        EC_WRITE_U8(domain_pd + off_dig_outAX[1], byte2);
        EC_WRITE_U8(domain_pd + off_dig_outAX[2], byte3);
        EC_WRITE_U8(domain_pd + off_dig_outAX[3], byte4);

        // send process data
        ecrt_domain_queue(domainPdo);
        ecrt_master_send(master);
    }
}

void motor_1_task(void *arg)
{   
   rt_task_set_periodic(NULL, TM_NOW, 300000); // ns

   while(1){
       if(rt_ethercat::getStart(0)){
         while(rt_ethercat::getSteps(0)>0){
             if(!rt_ethercat::getStart(0))
                 break;
             rt_ethercat::setPul_mt(0,true);
             rt_task_sleep(static_cast<RTIME>(rt_ethercat::getAxisSpeed()));///(30/5.7498)));
             rt_ethercat::setPul_mt(0,false);
             rt_task_sleep(static_cast<RTIME>(rt_ethercat::getAxisSpeed()));///(30/5.7498)));
             rt_ethercat::setSteps(0, rt_ethercat::getSteps(0)-1);
         }
         rt_ethercat::setStart(0, false);
       }
       rt_task_wait_period(NULL);
   }
}

void motor_2_task(void *arg)
{
    rt_task_set_periodic(NULL, TM_NOW, 300000); // ns

    while(1){
        if(rt_ethercat::getStart(1)){
          while(rt_ethercat::getSteps(1)>0){
              if(!rt_ethercat::getStart(1))
                  break;
              rt_ethercat::setPul_mt(1,true);
              rt_task_sleep(static_cast<RTIME>(rt_ethercat::getAxisSpeed()));///(50/5.7498)));
              rt_ethercat::setPul_mt(1,false);
              rt_task_sleep(static_cast<RTIME>(rt_ethercat::getAxisSpeed()));///(50/5.7498)));
              rt_ethercat::setSteps(1, rt_ethercat::getSteps(1)-1);
          }
          rt_ethercat::setStart(1, false);
        }
        rt_task_wait_period(NULL);
    }
}

void motor_3_task(void *arg)
{
    rt_task_set_periodic(NULL, TM_NOW, 300000); // ns

    while(1){
        if(rt_ethercat::getStart(2)){
          while(rt_ethercat::getSteps(2)>0){
              if(!rt_ethercat::getStart(2))
                  break;
              rt_ethercat::setPul_mt(2,true);
              rt_task_sleep(static_cast<RTIME>(rt_ethercat::getAxisSpeed()));///(30/5.7498)));
              rt_ethercat::setPul_mt(2,false);
              rt_task_sleep(static_cast<RTIME>(rt_ethercat::getAxisSpeed()));///(30/5.7498)));
              rt_ethercat::setSteps(2, rt_ethercat::getSteps(2)-1);
          }
          rt_ethercat::setStart(2, false);
        }
        rt_task_wait_period(NULL);
    }
}

void motor_4_task(void *arg)
{
    rt_task_set_periodic(NULL, TM_NOW, 300000); // ns

    while(1){
        if(rt_ethercat::getStart(3)){
          while(rt_ethercat::getSteps(3)>0){
              if(!rt_ethercat::getStart(3))
                  break;
              rt_ethercat::setPul_mt(3,true);
              rt_task_sleep(rt_ethercat::getAxisSpeed());
              rt_ethercat::setPul_mt(3,false);
              rt_task_sleep(rt_ethercat::getAxisSpeed());
              rt_ethercat::setSteps(3, rt_ethercat::getSteps(3)-1);
          }
          rt_ethercat::setStart(3, false);
        }
        rt_task_wait_period(NULL);
    }
}

void motor_5_task(void *arg)
{
    rt_task_set_periodic(NULL, TM_NOW, 300000); // ns

    while(1){
        if(rt_ethercat::getStart(4)){
          while(rt_ethercat::getSteps(4)>0){
              if(!rt_ethercat::getStart(4))
                  break;
              rt_ethercat::setPul_mt(4,true);
              rt_task_sleep(static_cast<RTIME>(rt_ethercat::getAxisSpeed()));///(27.138/5.7498)));
              rt_ethercat::setPul_mt(4,false);
              rt_task_sleep(static_cast<RTIME>(rt_ethercat::getAxisSpeed()));///(27.138/5.7498)));
              rt_ethercat::setSteps(4, rt_ethercat::getSteps(4)-1);
          }
          rt_ethercat::setStart(4, false);
        }
        rt_task_wait_period(NULL);
    }
}

void motor_6_task(void *arg)
{
    rt_task_set_periodic(NULL, TM_NOW, 300000); // ns

    while(1){
        if(rt_ethercat::getStart(5)){
          while(rt_ethercat::getSteps(5)>0){
              if(!rt_ethercat::getStart(5))
                  break;
              rt_ethercat::setPul_mt(5,true);
              rt_task_sleep(static_cast<RTIME>(rt_ethercat::getAxisSpeed()));///(10.3668/5.7498)));
              rt_ethercat::setPul_mt(5,false);
              rt_task_sleep(static_cast<RTIME>(rt_ethercat::getAxisSpeed()));///(10.3668/5.7498)));
              rt_ethercat::setSteps(5, rt_ethercat::getSteps(5)-1);
          }
          rt_ethercat::setStart(5, false);
        }
        rt_task_wait_period(NULL);
    }
}
/****************************************************************************
 * Signal handler
 ***************************************************************************/

void signal_handler(int sig)
{
    run = 0;
}

int rt_ethercat::rt_ethercat_start()
{   
    int ret;

    mlockall(MCL_CURRENT | MCL_FUTURE);

    master = ecrt_request_master(0);
    if (!master) {
        return -1;
    }

    domainPdo = ecrt_master_create_domain(master);
    if (!domainPdo) {
        return -1;
    }

//    domainPdoEK = ecrt_master_create_domain(master);
//    if (!domainPdoEK) {
//        return -1;
//    }

    printf("Creating slave configurations...\n");

    sc_dig_out_AX_01 =
        ecrt_master_slave_config(master, DigOutSlaveAX01_Pos, AX58100);
    if (!sc_dig_out_AX_01) {
        fprintf(stderr, "AX58100 Failed to get slave configuration.\n");
        return -1;
    }

    if (ecrt_slave_config_pdos(sc_dig_out_AX_01, EC_END, slave_syncs)) {
        fprintf(stderr, "AX58100 Failed to configure PDOs.\n");
        return -1;
    }

//    if (ecrt_domain_reg_pdo_entry_list(domainPdo, domain_pdo_regsAX)) {
//        fprintf(stderr, "AX58100 PDO entry registration failed!\n");
//        return -1;
//    }

    // Create configuration for bus coupler
      //sc = ecrt_master_slave_config(master, BusCoupler01_Pos, Beckhoff_EK1100);
      if (!ecrt_master_slave_config(master, BusCoupler01_Pos, Beckhoff_EK1100)) {
          return -1;
      }

      sc_dig_in_01 =
          ecrt_master_slave_config(master, DigInSlave01_Pos, Beckhoff_EL1014);
      if (!sc_dig_in_01) {
          fprintf(stderr, "EK Failed to get slave configuration.\n");
          return -1;
      }

      sc_dig_in_02 =
          ecrt_master_slave_config(master, DigInSlave02_Pos, Beckhoff_EL1018);
      if (!sc_dig_in_02) {
          fprintf(stderr, "EK Failed to get slave configuration.\n");
          return -1;
      }

      sc_dig_out_01 =
          ecrt_master_slave_config(master, DigOutSlave01_Pos, Beckhoff_EL2004);
      if (!sc_dig_out_01) {
          fprintf(stderr, "EK Failed to get slave configuration.\n");
          return -1;
      }

      sc_dig_out_02 =
          ecrt_master_slave_config(master, DigOutSlave02_Pos, Beckhoff_EL2008);
      if (!sc_dig_out_02) {
          fprintf(stderr, "EK Failed to get slave configuration.\n");
          return -1;
      }

      if (ecrt_slave_config_pdos(sc_dig_in_01, EC_END, slave_1_syncs)) {
          fprintf(stderr, "EK Failed to configure PDOs.\n");
          return -1;
      }

      if (ecrt_slave_config_pdos(sc_dig_in_02, EC_END, slave_2_syncs)) {
          fprintf(stderr, "EK Failed to configure PDOs.\n");
          return -1;
      }

      if (ecrt_slave_config_pdos(sc_dig_out_01, EC_END, slave_3_syncs)) {
          fprintf(stderr, "EK Failed to configure PDOs.\n");
          return -1;
      }

      if (ecrt_slave_config_pdos(sc_dig_out_02, EC_END, slave_4_syncs)) {
          fprintf(stderr, "EK Failed to configure PDOs.\n");
          return -1;
      }

      if (ecrt_domain_reg_pdo_entry_list(domainPdo, domain_pdo_regs)) {
          fprintf(stderr, "EK PDO entry registration failed!\n");
          return -1;
      }

    printf("Activating master...\n");
    if (ecrt_master_activate(master)) {
        return -1;
    }

    if (!(domain_pd = ecrt_domain_data(domainPdo))) {
        fprintf(stderr, "Failed to get domain data pointer.\n");
        return -1;
    }
//    if (!(domain_pd_EK = ecrt_domain_data(domainPdoEK))) {
//        fprintf(stderr, "Failed to get domain data pointer.\n");
//        return -1;
//    }
    printf("Version magic: %u.\n", ecrt_version_magic());

    ret = rt_task_create(&ec_task, "ec_task", 0, 80, 0);
    if (ret < 0) {
        fprintf(stderr, "Failed to create task: %s\n", strerror(-ret));
        return -1;
    }

    ret = rt_task_create(&mt_task, "mt_task", 0, 60, 0);
    if (ret < 0) {
        fprintf(stderr, "Failed to create task: %s\n", strerror(-ret));
        return -1;
    }

    ret = rt_task_create(&mt_2_task, "mt_2_task", 0, 60, 0);
    if (ret < 0) {
        fprintf(stderr, "Failed to create task: %s\n", strerror(-ret));
        return -1;
    }
    ret = rt_task_create(&mt_3_task, "mt_3_task", 0, 60, 0);
    if (ret < 0) {
        fprintf(stderr, "Failed to create task: %s\n", strerror(-ret));
        return -1;
    }
    ret = rt_task_create(&mt_4_task, "mt_4_task", 0, 60, 0);
    if (ret < 0) {
        fprintf(stderr, "Failed to create task: %s\n", strerror(-ret));
        return -1;
    }
    ret = rt_task_create(&mt_5_task, "mt_5_task", 0, 60, 0);
    if (ret < 0) {
        fprintf(stderr, "Failed to create task: %s\n", strerror(-ret));
        return -1;
    }
    ret = rt_task_create(&mt_6_task, "mt_6_task", 0, 60, 0);
    if (ret < 0) {
        fprintf(stderr, "Failed to create task: %s\n", strerror(-ret));
        return -1;
    }

    printf("Starting ec_task...\n");
    ret = rt_task_start(&ec_task, &ethercat_task, NULL);
    if (ret < 0) {
        fprintf(stderr, "Failed to start task: %s\n", strerror(-ret));
        return -1;
    }

    printf("Starting mt_task...\n");
    ret = rt_task_start(&mt_task, &motor_1_task, NULL);
    if (ret < 0) {
        fprintf(stderr, "Failed to start task: %s\n", strerror(-ret));
        return -1;
    }

    printf("Starting mt_2_task...\n");
    ret = rt_task_start(&mt_2_task, &motor_2_task, NULL);
    if (ret < 0) {
        fprintf(stderr, "Failed to start task: %s\n", strerror(-ret));
        return -1;
    }
    printf("Starting mt_3_task...\n");
    ret = rt_task_start(&mt_3_task, &motor_3_task, NULL);
    if (ret < 0) {
        fprintf(stderr, "Failed to start task: %s\n", strerror(-ret));
        return -1;
    }
    printf("Starting mt_4_task...\n");
    ret = rt_task_start(&mt_4_task, &motor_4_task, NULL);
    if (ret < 0) {
        fprintf(stderr, "Failed to start task: %s\n", strerror(-ret));
        return -1;
    }
    printf("Starting mt_5_task...\n");
    ret = rt_task_start(&mt_5_task, &motor_5_task, NULL);
    if (ret < 0) {
        fprintf(stderr, "Failed to start task: %s\n", strerror(-ret));
        return -1;
    }
    printf("Starting mt_6_task...\n");
    ret = rt_task_start(&mt_6_task, &motor_6_task, NULL);
    if (ret < 0) {
        fprintf(stderr, "Failed to start task: %s\n", strerror(-ret));
        return -1;
    }
}

//void rt_ethercat::state_outs(bool enable_mt_ex, bool dir_mt_ex, int steps_ex, bool start_ex)
//{
//   enable_mt = enable_mt_ex;
//   dir_mt = dir_mt_ex;
//   stepAxis[0] = steps_ex;
//   stepAxis[1] = steps_ex;
//   start_mt = start_ex;

//}
//void rt_ethercat::state_enable(bool enable_mt_ex)
//{
//    enable_mt = enable_mt_ex;
//}
//void rt_ethercat::state_dir(bool dir_mt_ex)
//{
//    dir_mt = dir_mt_ex;
//}
//void rt_ethercat::state_steps(int steps_ex)
//{
//    stepAxis[0] = steps_ex;
//    stepAxis[1] = steps_ex;
//}
//void rt_ethercat::state_start(int axisIndex)
//{
    //start_mt = start_ex;
//}
void rt_ethercat::rt_ethercat_stop()
{
    printf("Deleting realtime task...\n");
    rt_task_delete(&ec_task);
    rt_task_delete(&mt_task);

    printf("End of Program\n");
    ecrt_release_master(master);
}
