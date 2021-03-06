/* Include files */

#include <stddef.h>
#include "blas.h"
#include "aircraftControl_smallerStateEKF_sfun.h"
#include "c1_aircraftControl_smallerStateEKF.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "aircraftControl_smallerStateEKF_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c1_debug_family_names[13] = { "nargin", "nargout",
  "accelerations", "omega", "ALP", "BET", "u", "Vt", "H", "states_OUT",
  "cov_OUT", "nu", "S_OUT" };

static const char * c1_b_debug_family_names[110] = { "Q", "R", "F", "R2D", "g",
  "vs", "rho", "dt", "m", "deltaA", "deltaE", "deltaR", "throttle", "dE", "dA",
  "dR", "p", "q", "r", "CX_dE", "CY_dR", "CY_dE", "CZ_dE", "CZ_dA", "Cl_dA",
  "Cl_dR", "Cl_dE", "Cm_dE", "Cm_dA", "Cn_dA", "Cn_dR", "Cn_dE", "CX_dE1",
  "CX_dE2", "CY_dR1", "CY_dR2", "CY_dE1", "CZ_dE1", "CZ_dE2", "CZ_dA1", "Cl_dA1",
  "Cl_dA2", "Cl_dA3", "Cl_dR1", "Cl_dR2", "Cl_dE1", "Cm_dE1", "Cm_dE2", "Cm_dE3",
  "Cm_dA1", "Cn_dA1", "Cn_dA2", "Cn_dR1", "Cn_dR2", "Cn_dE1", "Cn_dE2", "S", "b",
  "cbar", "Ix", "Iy", "Iz", "Ixz", "xCG_ref", "xCG", "qbar", "hT", "Tmax", "T",
  "CX", "CY", "CZ", "Cl", "Cm", "Cn", "c1", "c2", "c3", "c4", "c5", "c6", "c7",
  "c8", "c9", "heng", "pdot", "qdot", "rdot", "pNew", "qNew", "rNew", "K", "H",
  "nargin", "nargout", "accelerations", "omega", "ALP", "BET", "u", "Vt",
  "states_OUT", "cov_OUT", "nu", "S_OUT", "states", "cov", "prev_p", "prev_q",
  "prev_r" };

/* Function Declarations */
static void initialize_c1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static void initialize_params_c1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static void enable_c1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static void disable_c1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static void set_sim_state_c1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_st);
static void finalize_c1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static void sf_gateway_c1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static void initSimStructsc1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static void c1_simulateEKF_smallerStateVec
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, real_T
   c1_accelerations[3], real_T c1_omega[3], real_T c1_ALP, real_T c1_BET, real_T
   c1_u[4], real_T c1_Vt, real_T c1_H, real_T c1_states_OUT[19], real_T
   c1_cov_OUT[19], real_T c1_nu[6], real_T c1_S_OUT[6]);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber);
static void c1_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_sprintf, const char_T *c1_identifier, char_T c1_y[14]);
static void c1_b_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y[14]);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static void c1_c_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_S_OUT, const char_T *c1_identifier, real_T c1_y[6]);
static void c1_d_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[6]);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_e_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_cov_OUT, const char_T *c1_identifier, real_T c1_y[19]);
static void c1_f_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[19]);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_g_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_h_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_b_prev_r, const char_T *c1_identifier);
static real_T c1_i_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_j_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_b_prev_q, const char_T *c1_identifier);
static real_T c1_k_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_l_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_b_prev_p, const char_T *c1_identifier);
static real_T c1_m_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_n_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_b_cov, const char_T *c1_identifier, real_T c1_y[361]);
static void c1_o_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[361]);
static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_j_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_p_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_b_states, const char_T *c1_identifier, real_T c1_y[19]);
static void c1_q_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[19]);
static void c1_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_r_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[4]);
static void c1_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_s_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[3]);
static void c1_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_k_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_t_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[36]);
static void c1_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_l_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_m_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_u_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[114]);
static void c1_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_n_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_v_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[361]);
static void c1_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_info_helper(const mxArray **c1_info);
static const mxArray *c1_emlrt_marshallOut(const char * c1_u);
static const mxArray *c1_b_emlrt_marshallOut(const uint32_T c1_u);
static void c1_b_info_helper(const mxArray **c1_info);
static void c1_c_info_helper(const mxArray **c1_info);
static void c1_d_info_helper(const mxArray **c1_info);
static real_T c1_mpower(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_a);
static real_T c1_power(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_a);
static void c1_eml_scalar_eg(SFc1_aircraftControl_smallerStateEKFInstanceStruct *
  chartInstance);
static void c1_eml_switch_helper
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static void c1_b_eml_switch_helper
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static void c1_b_power(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_a[361], real_T c1_y[361]);
static void c1_eye(SFc1_aircraftControl_smallerStateEKFInstanceStruct
                   *chartInstance, real_T c1_I[361]);
static real_T c1_b_mpower(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_a);
static real_T c1_c_mpower(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_a);
static void c1_b_eml_scalar_eg
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static void c1_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[361], real_T c1_B[361], real_T c1_C[361], real_T
  c1_b_C[361]);
static void c1_threshold(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance);
static void c1_c_eml_scalar_eg
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static void c1_b_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[114], real_T c1_B[361], real_T c1_C[114], real_T
  c1_b_C[114]);
static void c1_d_eml_scalar_eg
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static void c1_c_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[114], real_T c1_B[114], real_T c1_C[36], real_T
  c1_b_C[36]);
static void c1_e_eml_scalar_eg
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static void c1_f_eml_scalar_eg
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static void c1_d_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[361], real_T c1_B[114], real_T c1_C[114], real_T
  c1_b_C[114]);
static void c1_inv(SFc1_aircraftControl_smallerStateEKFInstanceStruct
                   *chartInstance, real_T c1_x[36], real_T c1_y[36]);
static void c1_eps(SFc1_aircraftControl_smallerStateEKFInstanceStruct
                   *chartInstance);
static void c1_eml_matlab_zgetrf
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, real_T
   c1_A[36], real_T c1_b_A[36], int32_T c1_ipiv[6], int32_T *c1_info);
static int32_T c1_eml_ixamax(SFc1_aircraftControl_smallerStateEKFInstanceStruct *
  chartInstance, int32_T c1_n, real_T c1_x[36], int32_T c1_ix0);
static void c1_check_forloop_overflow_error
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, boolean_T
   c1_overflow);
static void c1_b_threshold(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance);
static void c1_eml_xgeru(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, int32_T c1_m, int32_T c1_n, real_T c1_alpha1, int32_T c1_ix0,
  int32_T c1_iy0, real_T c1_A[36], int32_T c1_ia0, real_T c1_b_A[36]);
static void c1_eml_ipiv2perm(SFc1_aircraftControl_smallerStateEKFInstanceStruct *
  chartInstance, int32_T c1_ipiv[6], int32_T c1_perm[6]);
static void c1_eml_xtrsm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[36], real_T c1_B[36], real_T c1_b_B[36]);
static void c1_c_threshold(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance);
static real_T c1_norm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
                      *chartInstance, real_T c1_x[36]);
static void c1_eml_warning(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance);
static void c1_b_eml_warning(SFc1_aircraftControl_smallerStateEKFInstanceStruct *
  chartInstance, char_T c1_varargin_2[14]);
static void c1_g_eml_scalar_eg
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static void c1_e_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[114], real_T c1_B[36], real_T c1_C[114], real_T
  c1_b_C[114]);
static void c1_h_eml_scalar_eg
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static void c1_i_eml_scalar_eg
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);
static void c1_f_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[114], real_T c1_B[114], real_T c1_C[361], real_T
  c1_b_C[361]);
static void c1_diag(SFc1_aircraftControl_smallerStateEKFInstanceStruct
                    *chartInstance, real_T c1_v[361], real_T c1_d[19]);
static void c1_b_diag(SFc1_aircraftControl_smallerStateEKFInstanceStruct
                      *chartInstance, real_T c1_v[36], real_T c1_d[6]);
static const mxArray *c1_o_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_w_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_x_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_b_is_active_c1_aircraftControl_smallerStateEKF, const char_T
   *c1_identifier);
static uint8_T c1_y_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_g_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[361], real_T c1_B[361], real_T c1_C[361]);
static void c1_h_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[114], real_T c1_B[361], real_T c1_C[114]);
static void c1_i_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[114], real_T c1_B[114], real_T c1_C[36]);
static void c1_j_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[361], real_T c1_B[114], real_T c1_C[114]);
static void c1_b_eml_matlab_zgetrf
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, real_T
   c1_A[36], int32_T c1_ipiv[6], int32_T *c1_info);
static void c1_b_eml_xgeru(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, int32_T c1_m, int32_T c1_n, real_T c1_alpha1, int32_T c1_ix0,
  int32_T c1_iy0, real_T c1_A[36], int32_T c1_ia0);
static void c1_b_eml_xtrsm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[36], real_T c1_B[36]);
static void c1_k_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[114], real_T c1_B[36], real_T c1_C[114]);
static void c1_l_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[114], real_T c1_B[114], real_T c1_C[361]);
static void init_dsm_address_info
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c1_states_not_empty = false;
  chartInstance->c1_cov_not_empty = false;
  chartInstance->c1_prev_p_not_empty = false;
  chartInstance->c1_prev_q_not_empty = false;
  chartInstance->c1_prev_r_not_empty = false;
  chartInstance->c1_is_active_c1_aircraftControl_smallerStateEKF = 0U;
}

static void initialize_params_c1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c1_update_debugger_state_c1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  int32_T c1_i0;
  real_T c1_u[6];
  const mxArray *c1_b_y = NULL;
  int32_T c1_i1;
  real_T c1_b_u[19];
  const mxArray *c1_c_y = NULL;
  int32_T c1_i2;
  real_T c1_c_u[6];
  const mxArray *c1_d_y = NULL;
  int32_T c1_i3;
  real_T c1_d_u[19];
  const mxArray *c1_e_y = NULL;
  int32_T c1_i4;
  real_T c1_e_u[361];
  const mxArray *c1_f_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_f_u;
  const mxArray *c1_g_y = NULL;
  real_T c1_b_hoistedGlobal;
  real_T c1_g_u;
  const mxArray *c1_h_y = NULL;
  real_T c1_c_hoistedGlobal;
  real_T c1_h_u;
  const mxArray *c1_i_y = NULL;
  int32_T c1_i5;
  real_T c1_i_u[19];
  const mxArray *c1_j_y = NULL;
  uint8_T c1_d_hoistedGlobal;
  uint8_T c1_j_u;
  const mxArray *c1_k_y = NULL;
  real_T (*c1_states_OUT)[19];
  real_T (*c1_nu)[6];
  real_T (*c1_cov_OUT)[19];
  real_T (*c1_S_OUT)[6];
  c1_S_OUT = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 4);
  c1_nu = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 3);
  c1_cov_OUT = (real_T (*)[19])ssGetOutputPortSignal(chartInstance->S, 2);
  c1_states_OUT = (real_T (*)[19])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellmatrix(10, 1), false);
  for (c1_i0 = 0; c1_i0 < 6; c1_i0++) {
    c1_u[c1_i0] = (*c1_S_OUT)[c1_i0];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 6), false);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  for (c1_i1 = 0; c1_i1 < 19; c1_i1++) {
    c1_b_u[c1_i1] = (*c1_cov_OUT)[c1_i1];
  }

  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 1, 19), false);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  for (c1_i2 = 0; c1_i2 < 6; c1_i2++) {
    c1_c_u[c1_i2] = (*c1_nu)[c1_i2];
  }

  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 1, 6), false);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  for (c1_i3 = 0; c1_i3 < 19; c1_i3++) {
    c1_d_u[c1_i3] = (*c1_states_OUT)[c1_i3];
  }

  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", c1_d_u, 0, 0U, 1U, 0U, 1, 19), false);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  for (c1_i4 = 0; c1_i4 < 361; c1_i4++) {
    c1_e_u[c1_i4] = chartInstance->c1_cov[c1_i4];
  }

  c1_f_y = NULL;
  if (!chartInstance->c1_cov_not_empty) {
    sf_mex_assign(&c1_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_f_y, sf_mex_create("y", c1_e_u, 0, 0U, 1U, 0U, 2, 19, 19),
                  false);
  }

  sf_mex_setcell(c1_y, 4, c1_f_y);
  c1_hoistedGlobal = chartInstance->c1_prev_p;
  c1_f_u = c1_hoistedGlobal;
  c1_g_y = NULL;
  if (!chartInstance->c1_prev_p_not_empty) {
    sf_mex_assign(&c1_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_g_y, sf_mex_create("y", &c1_f_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c1_y, 5, c1_g_y);
  c1_b_hoistedGlobal = chartInstance->c1_prev_q;
  c1_g_u = c1_b_hoistedGlobal;
  c1_h_y = NULL;
  if (!chartInstance->c1_prev_q_not_empty) {
    sf_mex_assign(&c1_h_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_h_y, sf_mex_create("y", &c1_g_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c1_y, 6, c1_h_y);
  c1_c_hoistedGlobal = chartInstance->c1_prev_r;
  c1_h_u = c1_c_hoistedGlobal;
  c1_i_y = NULL;
  if (!chartInstance->c1_prev_r_not_empty) {
    sf_mex_assign(&c1_i_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_i_y, sf_mex_create("y", &c1_h_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c1_y, 7, c1_i_y);
  for (c1_i5 = 0; c1_i5 < 19; c1_i5++) {
    c1_i_u[c1_i5] = chartInstance->c1_states[c1_i5];
  }

  c1_j_y = NULL;
  if (!chartInstance->c1_states_not_empty) {
    sf_mex_assign(&c1_j_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_j_y, sf_mex_create("y", c1_i_u, 0, 0U, 1U, 0U, 1, 19),
                  false);
  }

  sf_mex_setcell(c1_y, 8, c1_j_y);
  c1_d_hoistedGlobal =
    chartInstance->c1_is_active_c1_aircraftControl_smallerStateEKF;
  c1_j_u = c1_d_hoistedGlobal;
  c1_k_y = NULL;
  sf_mex_assign(&c1_k_y, sf_mex_create("y", &c1_j_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 9, c1_k_y);
  sf_mex_assign(&c1_st, c1_y, false);
  return c1_st;
}

static void set_sim_state_c1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T c1_dv0[6];
  int32_T c1_i6;
  real_T c1_dv1[19];
  int32_T c1_i7;
  real_T c1_dv2[6];
  int32_T c1_i8;
  real_T c1_dv3[19];
  int32_T c1_i9;
  real_T c1_dv4[361];
  int32_T c1_i10;
  real_T c1_dv5[19];
  int32_T c1_i11;
  real_T (*c1_S_OUT)[6];
  real_T (*c1_cov_OUT)[19];
  real_T (*c1_nu)[6];
  real_T (*c1_states_OUT)[19];
  c1_S_OUT = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 4);
  c1_nu = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 3);
  c1_cov_OUT = (real_T (*)[19])ssGetOutputPortSignal(chartInstance->S, 2);
  c1_states_OUT = (real_T (*)[19])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = true;
  c1_u = sf_mex_dup(c1_st);
  c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)),
                        "S_OUT", c1_dv0);
  for (c1_i6 = 0; c1_i6 < 6; c1_i6++) {
    (*c1_S_OUT)[c1_i6] = c1_dv0[c1_i6];
  }

  c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 1)),
                        "cov_OUT", c1_dv1);
  for (c1_i7 = 0; c1_i7 < 19; c1_i7++) {
    (*c1_cov_OUT)[c1_i7] = c1_dv1[c1_i7];
  }

  c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 2)), "nu",
                        c1_dv2);
  for (c1_i8 = 0; c1_i8 < 6; c1_i8++) {
    (*c1_nu)[c1_i8] = c1_dv2[c1_i8];
  }

  c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 3)),
                        "states_OUT", c1_dv3);
  for (c1_i9 = 0; c1_i9 < 19; c1_i9++) {
    (*c1_states_OUT)[c1_i9] = c1_dv3[c1_i9];
  }

  c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 4)),
                        "cov", c1_dv4);
  for (c1_i10 = 0; c1_i10 < 361; c1_i10++) {
    chartInstance->c1_cov[c1_i10] = c1_dv4[c1_i10];
  }

  chartInstance->c1_prev_p = c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 5)), "prev_p");
  chartInstance->c1_prev_q = c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 6)), "prev_q");
  chartInstance->c1_prev_r = c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 7)), "prev_r");
  c1_p_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 8)),
                        "states", c1_dv5);
  for (c1_i11 = 0; c1_i11 < 19; c1_i11++) {
    chartInstance->c1_states[c1_i11] = c1_dv5[c1_i11];
  }

  chartInstance->c1_is_active_c1_aircraftControl_smallerStateEKF =
    c1_x_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 9)),
    "is_active_c1_aircraftControl_smallerStateEKF");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_aircraftControl_smallerStateEKF(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  int32_T c1_i12;
  int32_T c1_i13;
  int32_T c1_i14;
  real_T c1_hoistedGlobal;
  real_T c1_b_hoistedGlobal;
  real_T c1_c_hoistedGlobal;
  real_T c1_d_hoistedGlobal;
  int32_T c1_i15;
  real_T c1_accelerations[3];
  int32_T c1_i16;
  real_T c1_omega[3];
  real_T c1_ALP;
  real_T c1_BET;
  int32_T c1_i17;
  real_T c1_u[4];
  real_T c1_Vt;
  real_T c1_H;
  uint32_T c1_debug_family_var_map[13];
  real_T c1_nargin = 7.0;
  real_T c1_nargout = 4.0;
  real_T c1_states_OUT[19];
  real_T c1_cov_OUT[19];
  real_T c1_nu[6];
  real_T c1_S_OUT[6];
  int32_T c1_i18;
  real_T c1_b_accelerations[3];
  int32_T c1_i19;
  real_T c1_b_omega[3];
  int32_T c1_i20;
  real_T c1_b_u[4];
  real_T c1_b_S_OUT[6];
  real_T c1_b_nu[6];
  real_T c1_b_cov_OUT[19];
  real_T c1_b_states_OUT[19];
  int32_T c1_i21;
  int32_T c1_i22;
  int32_T c1_i23;
  int32_T c1_i24;
  int32_T c1_i25;
  int32_T c1_i26;
  int32_T c1_i27;
  int32_T c1_i28;
  int32_T c1_i29;
  int32_T c1_i30;
  int32_T c1_i31;
  int32_T c1_i32;
  real_T *c1_b_ALP;
  real_T *c1_b_BET;
  real_T *c1_b_Vt;
  real_T *c1_b_H;
  real_T (*c1_c_states_OUT)[19];
  real_T (*c1_c_cov_OUT)[19];
  real_T (*c1_c_nu)[6];
  real_T (*c1_c_S_OUT)[6];
  real_T (*c1_c_u)[4];
  real_T (*c1_c_omega)[3];
  real_T (*c1_c_accelerations)[3];
  c1_c_S_OUT = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 4);
  c1_c_nu = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 3);
  c1_b_H = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c1_c_cov_OUT = (real_T (*)[19])ssGetOutputPortSignal(chartInstance->S, 2);
  c1_b_Vt = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c1_c_states_OUT = (real_T (*)[19])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_c_u = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 4);
  c1_b_BET = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c1_b_ALP = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c1_c_omega = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c1_c_accelerations = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i12 = 0; c1_i12 < 3; c1_i12++) {
    _SFD_DATA_RANGE_CHECK((*c1_c_accelerations)[c1_i12], 0U);
  }

  for (c1_i13 = 0; c1_i13 < 3; c1_i13++) {
    _SFD_DATA_RANGE_CHECK((*c1_c_omega)[c1_i13], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*c1_b_ALP, 2U);
  _SFD_DATA_RANGE_CHECK(*c1_b_BET, 3U);
  for (c1_i14 = 0; c1_i14 < 4; c1_i14++) {
    _SFD_DATA_RANGE_CHECK((*c1_c_u)[c1_i14], 4U);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  c1_hoistedGlobal = *c1_b_ALP;
  c1_b_hoistedGlobal = *c1_b_BET;
  c1_c_hoistedGlobal = *c1_b_Vt;
  c1_d_hoistedGlobal = *c1_b_H;
  for (c1_i15 = 0; c1_i15 < 3; c1_i15++) {
    c1_accelerations[c1_i15] = (*c1_c_accelerations)[c1_i15];
  }

  for (c1_i16 = 0; c1_i16 < 3; c1_i16++) {
    c1_omega[c1_i16] = (*c1_c_omega)[c1_i16];
  }

  c1_ALP = c1_hoistedGlobal;
  c1_BET = c1_b_hoistedGlobal;
  for (c1_i17 = 0; c1_i17 < 4; c1_i17++) {
    c1_u[c1_i17] = (*c1_c_u)[c1_i17];
  }

  c1_Vt = c1_c_hoistedGlobal;
  c1_H = c1_d_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 13U, 13U, c1_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 0U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 1U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_accelerations, 2U, c1_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_omega, 3U, c1_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_ALP, 4U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_BET, 5U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_u, 6U, c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_Vt, 7U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_H, 8U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_states_OUT, 9U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_cov_OUT, 10U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_nu, 11U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_S_OUT, 12U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 4);
  for (c1_i18 = 0; c1_i18 < 3; c1_i18++) {
    c1_b_accelerations[c1_i18] = c1_accelerations[c1_i18];
  }

  for (c1_i19 = 0; c1_i19 < 3; c1_i19++) {
    c1_b_omega[c1_i19] = c1_omega[c1_i19];
  }

  for (c1_i20 = 0; c1_i20 < 4; c1_i20++) {
    c1_b_u[c1_i20] = c1_u[c1_i20];
  }

  c1_simulateEKF_smallerStateVec(chartInstance, c1_b_accelerations, c1_b_omega,
    c1_ALP, c1_BET, c1_b_u, c1_Vt, c1_H, c1_b_states_OUT, c1_b_cov_OUT, c1_b_nu,
    c1_b_S_OUT);
  for (c1_i21 = 0; c1_i21 < 19; c1_i21++) {
    c1_states_OUT[c1_i21] = c1_b_states_OUT[c1_i21];
  }

  for (c1_i22 = 0; c1_i22 < 19; c1_i22++) {
    c1_cov_OUT[c1_i22] = c1_b_cov_OUT[c1_i22];
  }

  for (c1_i23 = 0; c1_i23 < 6; c1_i23++) {
    c1_nu[c1_i23] = c1_b_nu[c1_i23];
  }

  for (c1_i24 = 0; c1_i24 < 6; c1_i24++) {
    c1_S_OUT[c1_i24] = c1_b_S_OUT[c1_i24];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  for (c1_i25 = 0; c1_i25 < 19; c1_i25++) {
    (*c1_c_states_OUT)[c1_i25] = c1_states_OUT[c1_i25];
  }

  for (c1_i26 = 0; c1_i26 < 19; c1_i26++) {
    (*c1_c_cov_OUT)[c1_i26] = c1_cov_OUT[c1_i26];
  }

  for (c1_i27 = 0; c1_i27 < 6; c1_i27++) {
    (*c1_c_nu)[c1_i27] = c1_nu[c1_i27];
  }

  for (c1_i28 = 0; c1_i28 < 6; c1_i28++) {
    (*c1_c_S_OUT)[c1_i28] = c1_S_OUT[c1_i28];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY
    (_aircraftControl_smallerStateEKFMachineNumber_, chartInstance->chartNumber,
     chartInstance->instanceNumber);
  for (c1_i29 = 0; c1_i29 < 19; c1_i29++) {
    _SFD_DATA_RANGE_CHECK((*c1_c_states_OUT)[c1_i29], 5U);
  }

  _SFD_DATA_RANGE_CHECK(*c1_b_Vt, 6U);
  for (c1_i30 = 0; c1_i30 < 19; c1_i30++) {
    _SFD_DATA_RANGE_CHECK((*c1_c_cov_OUT)[c1_i30], 7U);
  }

  _SFD_DATA_RANGE_CHECK(*c1_b_H, 8U);
  for (c1_i31 = 0; c1_i31 < 6; c1_i31++) {
    _SFD_DATA_RANGE_CHECK((*c1_c_nu)[c1_i31], 9U);
  }

  for (c1_i32 = 0; c1_i32 < 6; c1_i32++) {
    _SFD_DATA_RANGE_CHECK((*c1_c_S_OUT)[c1_i32], 10U);
  }
}

static void initSimStructsc1_aircraftControl_smallerStateEKF
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_simulateEKF_smallerStateVec
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, real_T
   c1_accelerations[3], real_T c1_omega[3], real_T c1_ALP, real_T c1_BET, real_T
   c1_u[4], real_T c1_Vt, real_T c1_H, real_T c1_states_OUT[19], real_T
   c1_cov_OUT[19], real_T c1_nu[6], real_T c1_S_OUT[6])
{
  uint32_T c1_debug_family_var_map[110];
  real_T c1_Q[361];
  real_T c1_R[36];
  real_T c1_F[361];
  real_T c1_R2D;
  real_T c1_g;
  real_T c1_vs;
  real_T c1_rho;
  real_T c1_dt;
  real_T c1_m;
  real_T c1_deltaA;
  real_T c1_deltaE;
  real_T c1_deltaR;
  real_T c1_throttle;
  real_T c1_dE;
  real_T c1_dA;
  real_T c1_dR;
  real_T c1_p;
  real_T c1_q;
  real_T c1_r;
  real_T c1_CX_dE;
  real_T c1_CY_dR;
  real_T c1_CY_dE;
  real_T c1_CZ_dE;
  real_T c1_CZ_dA;
  real_T c1_Cl_dA;
  real_T c1_Cl_dR;
  real_T c1_Cl_dE;
  real_T c1_Cm_dE;
  real_T c1_Cm_dA;
  real_T c1_Cn_dA;
  real_T c1_Cn_dR;
  real_T c1_Cn_dE;
  real_T c1_CX_dE1;
  real_T c1_CX_dE2;
  real_T c1_CY_dR1;
  real_T c1_CY_dR2;
  real_T c1_CY_dE1;
  real_T c1_CZ_dE1;
  real_T c1_CZ_dE2;
  real_T c1_CZ_dA1;
  real_T c1_Cl_dA1;
  real_T c1_Cl_dA2;
  real_T c1_Cl_dA3;
  real_T c1_Cl_dR1;
  real_T c1_Cl_dR2;
  real_T c1_Cl_dE1;
  real_T c1_Cm_dE1;
  real_T c1_Cm_dE2;
  real_T c1_Cm_dE3;
  real_T c1_Cm_dA1;
  real_T c1_Cn_dA1;
  real_T c1_Cn_dA2;
  real_T c1_Cn_dR1;
  real_T c1_Cn_dR2;
  real_T c1_Cn_dE1;
  real_T c1_Cn_dE2;
  real_T c1_S;
  real_T c1_b;
  real_T c1_cbar;
  real_T c1_Ix;
  real_T c1_Iy;
  real_T c1_Iz;
  real_T c1_Ixz;
  real_T c1_xCG_ref;
  real_T c1_xCG;
  real_T c1_qbar;
  real_T c1_hT;
  real_T c1_Tmax;
  real_T c1_T;
  real_T c1_CX;
  real_T c1_CY;
  real_T c1_CZ;
  real_T c1_Cl;
  real_T c1_Cm;
  real_T c1_Cn;
  real_T c1_c1;
  real_T c1_c2;
  real_T c1_c3;
  real_T c1_c4;
  real_T c1_c5;
  real_T c1_c6;
  real_T c1_c7;
  real_T c1_c8;
  real_T c1_c9;
  real_T c1_heng;
  real_T c1_pdot;
  real_T c1_qdot;
  real_T c1_rdot;
  real_T c1_pNew;
  real_T c1_qNew;
  real_T c1_rNew;
  real_T c1_K[114];
  real_T c1_b_H[114];
  real_T c1_b_S[36];
  real_T c1_nargin = 7.0;
  real_T c1_nargout = 4.0;
  int32_T c1_i33;
  int32_T c1_i34;
  int32_T c1_i35;
  static real_T c1_dv6[361] = { 0.001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.001 };

  real_T c1_dv7[361];
  real_T c1_dv8[361];
  int32_T c1_i36;
  int32_T c1_i37;
  static real_T c1_dv9[36] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  int32_T c1_i38;
  int32_T c1_i39;
  int32_T c1_i40;
  int32_T c1_i41;
  static real_T c1_y[9] = { 0.010000000000000002, 0.0, 0.0, 0.0,
    0.010000000000000002, 0.0, 0.0, 0.0, 0.010000000000000002 };

  int32_T c1_i42;
  int32_T c1_i43;
  int32_T c1_i44;
  int32_T c1_i45;
  real_T c1_a[9];
  int32_T c1_i46;
  int32_T c1_i47;
  int32_T c1_i48;
  int32_T c1_i49;
  int32_T c1_i50;
  real_T c1_dv10[361];
  int32_T c1_i51;
  real_T c1_A;
  real_T c1_x;
  real_T c1_b_x;
  real_T c1_c_x;
  real_T c1_b_A;
  real_T c1_d_x;
  real_T c1_e_x;
  real_T c1_f_x;
  real_T c1_b_y;
  real_T c1_c_A;
  real_T c1_g_x;
  real_T c1_h_x;
  real_T c1_i_x;
  real_T c1_c_y;
  real_T c1_d_A;
  real_T c1_j_x;
  real_T c1_k_x;
  real_T c1_l_x;
  real_T c1_d_y;
  real_T c1_e_A;
  real_T c1_m_x;
  real_T c1_n_x;
  real_T c1_o_x;
  real_T c1_e_y;
  real_T c1_f_A;
  real_T c1_p_x;
  real_T c1_q_x;
  real_T c1_r_x;
  real_T c1_g_A;
  real_T c1_s_x;
  real_T c1_t_x;
  real_T c1_u_x;
  real_T c1_f_y;
  real_T c1_h_A;
  real_T c1_v_x;
  real_T c1_w_x;
  real_T c1_x_x;
  real_T c1_g_y;
  real_T c1_i_A;
  real_T c1_B;
  real_T c1_y_x;
  real_T c1_h_y;
  real_T c1_ab_x;
  real_T c1_i_y;
  real_T c1_bb_x;
  real_T c1_j_y;
  real_T c1_k_y;
  real_T c1_b_B;
  real_T c1_l_y;
  real_T c1_m_y;
  real_T c1_n_y;
  real_T c1_o_y;
  real_T c1_j_A;
  real_T c1_cb_x;
  real_T c1_db_x;
  real_T c1_eb_x;
  real_T c1_p_y;
  real_T c1_k_A;
  real_T c1_fb_x;
  real_T c1_gb_x;
  real_T c1_hb_x;
  real_T c1_q_y;
  real_T c1_l_A;
  real_T c1_c_B;
  real_T c1_ib_x;
  real_T c1_r_y;
  real_T c1_jb_x;
  real_T c1_s_y;
  real_T c1_kb_x;
  real_T c1_t_y;
  real_T c1_u_y;
  real_T c1_d_B;
  real_T c1_v_y;
  real_T c1_w_y;
  real_T c1_x_y;
  real_T c1_y_y;
  real_T c1_m_A;
  real_T c1_lb_x;
  real_T c1_mb_x;
  real_T c1_nb_x;
  real_T c1_ab_y;
  real_T c1_n_A;
  real_T c1_ob_x;
  real_T c1_pb_x;
  real_T c1_qb_x;
  real_T c1_bb_y;
  real_T c1_o_A;
  real_T c1_e_B;
  real_T c1_rb_x;
  real_T c1_cb_y;
  real_T c1_sb_x;
  real_T c1_db_y;
  real_T c1_tb_x;
  real_T c1_eb_y;
  real_T c1_fb_y;
  real_T c1_f_B;
  real_T c1_gb_y;
  real_T c1_hb_y;
  real_T c1_ib_y;
  real_T c1_jb_y;
  real_T c1_p_A;
  real_T c1_ub_x;
  real_T c1_vb_x;
  real_T c1_wb_x;
  real_T c1_kb_y;
  real_T c1_q_A;
  real_T c1_xb_x;
  real_T c1_yb_x;
  real_T c1_ac_x;
  real_T c1_lb_y;
  real_T c1_r_A;
  real_T c1_bc_x;
  real_T c1_cc_x;
  real_T c1_dc_x;
  real_T c1_mb_y;
  real_T c1_hoistedGlobal;
  real_T c1_s_A;
  real_T c1_ec_x;
  real_T c1_fc_x;
  real_T c1_gc_x;
  real_T c1_nb_y;
  real_T c1_b_hoistedGlobal;
  real_T c1_t_A;
  real_T c1_hc_x;
  real_T c1_ic_x;
  real_T c1_jc_x;
  real_T c1_ob_y;
  real_T c1_c_hoistedGlobal;
  real_T c1_u_A;
  real_T c1_kc_x;
  real_T c1_lc_x;
  real_T c1_mc_x;
  real_T c1_pb_y;
  real_T c1_v_A;
  real_T c1_g_B;
  real_T c1_nc_x;
  real_T c1_qb_y;
  real_T c1_oc_x;
  real_T c1_rb_y;
  real_T c1_pc_x;
  real_T c1_sb_y;
  real_T c1_tb_y;
  real_T c1_w_A;
  real_T c1_h_B;
  real_T c1_qc_x;
  real_T c1_ub_y;
  real_T c1_rc_x;
  real_T c1_vb_y;
  real_T c1_sc_x;
  real_T c1_wb_y;
  real_T c1_xb_y;
  real_T c1_x_A;
  real_T c1_i_B;
  real_T c1_tc_x;
  real_T c1_yb_y;
  real_T c1_uc_x;
  real_T c1_ac_y;
  real_T c1_vc_x;
  real_T c1_bc_y;
  real_T c1_cc_y;
  real_T c1_y_A;
  real_T c1_j_B;
  real_T c1_wc_x;
  real_T c1_dc_y;
  real_T c1_xc_x;
  real_T c1_ec_y;
  real_T c1_yc_x;
  real_T c1_fc_y;
  real_T c1_gc_y;
  real_T c1_ab_A;
  real_T c1_k_B;
  real_T c1_ad_x;
  real_T c1_hc_y;
  real_T c1_bd_x;
  real_T c1_ic_y;
  real_T c1_cd_x;
  real_T c1_jc_y;
  real_T c1_kc_y;
  real_T c1_bb_A;
  real_T c1_l_B;
  real_T c1_dd_x;
  real_T c1_lc_y;
  real_T c1_ed_x;
  real_T c1_mc_y;
  real_T c1_fd_x;
  real_T c1_nc_y;
  real_T c1_oc_y;
  real_T c1_cb_A;
  real_T c1_m_B;
  real_T c1_gd_x;
  real_T c1_pc_y;
  real_T c1_hd_x;
  real_T c1_qc_y;
  real_T c1_id_x;
  real_T c1_rc_y;
  real_T c1_sc_y;
  real_T c1_db_A;
  real_T c1_n_B;
  real_T c1_jd_x;
  real_T c1_tc_y;
  real_T c1_kd_x;
  real_T c1_uc_y;
  real_T c1_ld_x;
  real_T c1_vc_y;
  real_T c1_wc_y;
  real_T c1_eb_A;
  real_T c1_o_B;
  real_T c1_md_x;
  real_T c1_xc_y;
  real_T c1_nd_x;
  real_T c1_yc_y;
  real_T c1_od_x;
  real_T c1_ad_y;
  real_T c1_bd_y;
  real_T c1_fb_A;
  real_T c1_p_B;
  real_T c1_pd_x;
  real_T c1_cd_y;
  real_T c1_qd_x;
  real_T c1_dd_y;
  real_T c1_rd_x;
  real_T c1_ed_y;
  real_T c1_fd_y;
  real_T c1_gb_A;
  real_T c1_q_B;
  real_T c1_sd_x;
  real_T c1_gd_y;
  real_T c1_td_x;
  real_T c1_hd_y;
  real_T c1_ud_x;
  real_T c1_id_y;
  real_T c1_jd_y;
  real_T c1_hb_A;
  real_T c1_r_B;
  real_T c1_vd_x;
  real_T c1_kd_y;
  real_T c1_wd_x;
  real_T c1_ld_y;
  real_T c1_xd_x;
  real_T c1_md_y;
  real_T c1_nd_y;
  real_T c1_ib_A;
  real_T c1_s_B;
  real_T c1_yd_x;
  real_T c1_od_y;
  real_T c1_ae_x;
  real_T c1_pd_y;
  real_T c1_be_x;
  real_T c1_qd_y;
  real_T c1_rd_y;
  real_T c1_jb_A;
  real_T c1_t_B;
  real_T c1_ce_x;
  real_T c1_sd_y;
  real_T c1_de_x;
  real_T c1_td_y;
  real_T c1_ee_x;
  real_T c1_ud_y;
  real_T c1_vd_y;
  real_T c1_kb_A;
  real_T c1_u_B;
  real_T c1_fe_x;
  real_T c1_wd_y;
  real_T c1_ge_x;
  real_T c1_xd_y;
  real_T c1_he_x;
  real_T c1_yd_y;
  real_T c1_ae_y;
  real_T c1_lb_A;
  real_T c1_v_B;
  real_T c1_ie_x;
  real_T c1_be_y;
  real_T c1_je_x;
  real_T c1_ce_y;
  real_T c1_ke_x;
  real_T c1_de_y;
  real_T c1_ee_y;
  real_T c1_mb_A;
  real_T c1_w_B;
  real_T c1_le_x;
  real_T c1_fe_y;
  real_T c1_me_x;
  real_T c1_ge_y;
  real_T c1_ne_x;
  real_T c1_he_y;
  real_T c1_ie_y;
  real_T c1_nb_A;
  real_T c1_x_B;
  real_T c1_oe_x;
  real_T c1_je_y;
  real_T c1_pe_x;
  real_T c1_ke_y;
  real_T c1_qe_x;
  real_T c1_le_y;
  real_T c1_me_y;
  int32_T c1_i52;
  real_T c1_d_hoistedGlobal[361];
  int32_T c1_i53;
  real_T c1_b_a[361];
  int32_T c1_i54;
  real_T c1_ne_y[361];
  int32_T c1_i55;
  real_T c1_c_a[361];
  int32_T c1_i56;
  real_T c1_e_hoistedGlobal[361];
  int32_T c1_i57;
  int32_T c1_i58;
  int32_T c1_i59;
  int32_T c1_i60;
  int32_T c1_i61;
  int32_T c1_i62;
  real_T c1_oe_y[361];
  int32_T c1_i63;
  real_T c1_f_hoistedGlobal[361];
  int32_T c1_i64;
  int32_T c1_i65;
  static real_T c1_d_a[114] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  int32_T c1_i66;
  int32_T c1_i67;
  real_T c1_pe_y[114];
  int32_T c1_i68;
  real_T c1_e_a[114];
  int32_T c1_i69;
  real_T c1_g_hoistedGlobal[361];
  int32_T c1_i70;
  real_T c1_qe_y[36];
  int32_T c1_i71;
  real_T c1_re_y[114];
  int32_T c1_i72;
  static real_T c1_b_b[114] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  real_T c1_c_b[114];
  int32_T c1_i73;
  int32_T c1_i74;
  real_T c1_h_hoistedGlobal[19];
  int32_T c1_i75;
  real_T c1_se_y[6];
  int32_T c1_i76;
  int32_T c1_i77;
  int32_T c1_i78;
  real_T c1_b_accelerations[6];
  int32_T c1_i79;
  int32_T c1_i80;
  int32_T c1_i81;
  int32_T c1_i82;
  real_T c1_te_y[114];
  int32_T c1_i83;
  real_T c1_i_hoistedGlobal[361];
  int32_T c1_i84;
  real_T c1_d_b[114];
  int32_T c1_i85;
  real_T c1_c_S[36];
  int32_T c1_i86;
  int32_T c1_i87;
  int32_T c1_i88;
  real_T c1_dv11[114];
  int32_T c1_i89;
  real_T c1_dv12[36];
  int32_T c1_i90;
  real_T c1_dv13[114];
  int32_T c1_i91;
  real_T c1_dv14[36];
  int32_T c1_i92;
  int32_T c1_i93;
  real_T c1_f_a[114];
  int32_T c1_i94;
  int32_T c1_i95;
  real_T c1_ue_y[19];
  int32_T c1_i96;
  int32_T c1_i97;
  int32_T c1_i98;
  int32_T c1_i99;
  int32_T c1_i100;
  int32_T c1_i101;
  int32_T c1_i102;
  int32_T c1_i103;
  real_T c1_g_a[114];
  int32_T c1_i104;
  real_T c1_ve_y[36];
  int32_T c1_i105;
  int32_T c1_i106;
  int32_T c1_i107;
  int32_T c1_i108;
  int32_T c1_i109;
  int32_T c1_i110;
  real_T c1_we_y[114];
  int32_T c1_i111;
  real_T c1_xe_y[114];
  int32_T c1_i112;
  int32_T c1_i113;
  int32_T c1_i114;
  real_T c1_dv15[361];
  real_T c1_dv16[19];
  int32_T c1_i115;
  int32_T c1_i116;
  real_T c1_d_S[36];
  real_T c1_dv17[6];
  int32_T c1_i117;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 110U, 112U, c1_b_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_Q, 0U, c1_n_sf_marshallOut,
    c1_m_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_R, 1U, c1_k_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_F, 2U, c1_n_sf_marshallOut,
    c1_m_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_R2D, 3U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_g, 4U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_vs, 5U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_rho, 6U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_dt, 7U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_m, 8U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_deltaA, 9U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_deltaE, 10U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_deltaR, 11U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_throttle, 12U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_dE, 13U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_dA, 14U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_dR, 15U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_p, 16U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_q, 17U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_r, 18U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_CX_dE, 19U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_CY_dR, 20U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_CY_dE, 21U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_CZ_dE, 22U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_CZ_dA, 23U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cl_dA, 24U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cl_dR, 25U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cl_dE, 26U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cm_dE, 27U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cm_dA, 28U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cn_dA, 29U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cn_dR, 30U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cn_dE, 31U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_CX_dE1, 32U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_CX_dE2, 33U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_CY_dR1, 34U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_CY_dR2, 35U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_CY_dE1, 36U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_CZ_dE1, 37U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_CZ_dE2, 38U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_CZ_dA1, 39U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cl_dA1, 40U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cl_dA2, 41U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cl_dA3, 42U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cl_dR1, 43U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cl_dR2, 44U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cl_dE1, 45U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cm_dE1, 46U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cm_dE2, 47U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cm_dE3, 48U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cm_dA1, 49U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cn_dA1, 50U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cn_dA2, 51U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cn_dR1, 52U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cn_dR2, 53U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cn_dE1, 54U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cn_dE2, 55U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_S, MAX_uint32_T, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b, 57U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_cbar, 58U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_Ix, 59U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_Iy, 60U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_Iz, 61U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_Ixz, 62U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_xCG_ref, 63U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_xCG, 64U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_qbar, 65U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_hT, 66U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Tmax, 67U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_T, 68U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_CX, 69U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_CY, 70U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_CZ, 71U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cl, 72U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cm, 73U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Cn, 74U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_c1, 75U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_c2, 76U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_c3, 77U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_c4, 78U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_c5, 79U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_c6, 80U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_c7, 81U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_c8, 82U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_c9, 83U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_heng, 84U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_pdot, 85U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_qdot, 86U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_rdot, 87U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_pNew, 88U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_qNew, 89U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_rNew, 90U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_K, 91U, c1_m_sf_marshallOut,
    c1_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_H, MAX_uint32_T, c1_l_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_b_S, MAX_uint32_T, c1_k_sf_marshallOut,
    c1_k_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 93U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 94U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_accelerations, 95U,
    c1_e_sf_marshallOut, c1_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_omega, 96U, c1_e_sf_marshallOut,
    c1_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_ALP, 97U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_BET, 98U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_u, 99U, c1_d_sf_marshallOut,
    c1_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Vt, 100U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_H, 92U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_states_OUT, 101U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_cov_OUT, 102U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_nu, 103U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_S_OUT, 104U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c1_states, 105U,
    c1_j_sf_marshallOut, c1_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c1_cov, 106U,
    c1_i_sf_marshallOut, c1_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_prev_p, 107U,
    c1_h_sf_marshallOut, c1_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_prev_q, 108U,
    c1_g_sf_marshallOut, c1_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_prev_r, 109U,
    c1_f_sf_marshallOut, c1_d_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 2);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 5);
  if (CV_SCRIPT_IF(0, 0, !chartInstance->c1_states_not_empty)) {
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 6);
    for (c1_i33 = 0; c1_i33 < 19; c1_i33++) {
      chartInstance->c1_states[c1_i33] = 0.0;
    }

    chartInstance->c1_states_not_empty = true;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 7);
    for (c1_i34 = 0; c1_i34 < 361; c1_i34++) {
      chartInstance->c1_cov[c1_i34] = 0.0;
    }

    chartInstance->c1_cov_not_empty = true;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 9);
    chartInstance->c1_states[0] = c1_accelerations[0];
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 9);
    chartInstance->c1_cov[0] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 10);
    chartInstance->c1_states[1] = c1_accelerations[1];
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 10);
    chartInstance->c1_cov[20] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 11);
    chartInstance->c1_states[2] = c1_accelerations[2];
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 11);
    chartInstance->c1_cov[40] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 13);
    chartInstance->c1_states[3] = c1_omega[0];
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 13);
    chartInstance->c1_cov[60] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 14);
    chartInstance->c1_states[4] = c1_omega[1];
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 14);
    chartInstance->c1_cov[80] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 15);
    chartInstance->c1_states[5] = c1_omega[2];
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 15);
    chartInstance->c1_cov[100] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 17);
    chartInstance->c1_states[6] = 1.0;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 17);
    chartInstance->c1_cov[120] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 18);
    chartInstance->c1_states[7] = 1.0;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 18);
    chartInstance->c1_cov[140] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 20);
    chartInstance->c1_states[8] = 1.0;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 20);
    chartInstance->c1_cov[160] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 21);
    chartInstance->c1_states[9] = 1.0;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 21);
    chartInstance->c1_cov[180] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 22);
    chartInstance->c1_states[10] = 1.0;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 22);
    chartInstance->c1_cov[200] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 24);
    chartInstance->c1_states[11] = 1.0;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 24);
    chartInstance->c1_cov[220] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 25);
    chartInstance->c1_states[12] = 1.0;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 25);
    chartInstance->c1_cov[240] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 26);
    chartInstance->c1_states[13] = 1.0;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 26);
    chartInstance->c1_cov[260] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 28);
    chartInstance->c1_states[14] = 1.0;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 28);
    chartInstance->c1_cov[280] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 29);
    chartInstance->c1_states[15] = 1.0;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 29);
    chartInstance->c1_cov[300] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 30);
    chartInstance->c1_states[16] = 1.0;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 30);
    chartInstance->c1_cov[320] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 31);
    chartInstance->c1_states[17] = 1.0;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 31);
    chartInstance->c1_cov[340] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 32);
    chartInstance->c1_states[18] = 1.0;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 32);
    chartInstance->c1_cov[360] = c1_mpower(chartInstance, 0.1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 34);
    chartInstance->c1_prev_p = 0.0;
    chartInstance->c1_prev_p_not_empty = true;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 35);
    chartInstance->c1_prev_q = 0.0;
    chartInstance->c1_prev_q_not_empty = true;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 36);
    chartInstance->c1_prev_r = 0.0;
    chartInstance->c1_prev_r_not_empty = true;
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 42);
  for (c1_i35 = 0; c1_i35 < 361; c1_i35++) {
    c1_dv7[c1_i35] = c1_dv6[c1_i35];
  }

  c1_b_power(chartInstance, c1_dv7, c1_dv8);
  for (c1_i36 = 0; c1_i36 < 361; c1_i36++) {
    c1_Q[c1_i36] = c1_dv8[c1_i36];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 43);
  for (c1_i37 = 0; c1_i37 < 36; c1_i37++) {
    c1_R[c1_i37] = c1_dv9[c1_i37];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 44);
  c1_i38 = 0;
  c1_i39 = 0;
  for (c1_i40 = 0; c1_i40 < 3; c1_i40++) {
    for (c1_i41 = 0; c1_i41 < 3; c1_i41++) {
      c1_R[c1_i41 + c1_i38] = c1_y[c1_i41 + c1_i39];
    }

    c1_i38 += 6;
    c1_i39 += 3;
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 45);
  c1_i42 = 0;
  c1_i43 = 0;
  for (c1_i44 = 0; c1_i44 < 3; c1_i44++) {
    for (c1_i45 = 0; c1_i45 < 3; c1_i45++) {
      c1_a[c1_i45 + c1_i42] = c1_R[(c1_i45 + c1_i43) + 21];
    }

    c1_i42 += 3;
    c1_i43 += 6;
  }

  for (c1_i46 = 0; c1_i46 < 9; c1_i46++) {
    c1_a[c1_i46] *= 0.010000000000000002;
  }

  c1_i47 = 0;
  c1_i48 = 0;
  for (c1_i49 = 0; c1_i49 < 3; c1_i49++) {
    for (c1_i50 = 0; c1_i50 < 3; c1_i50++) {
      c1_R[(c1_i50 + c1_i47) + 21] = c1_a[c1_i50 + c1_i48];
    }

    c1_i47 += 6;
    c1_i48 += 3;
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 46);
  c1_eye(chartInstance, c1_dv10);
  for (c1_i51 = 0; c1_i51 < 361; c1_i51++) {
    c1_F[c1_i51] = c1_dv10[c1_i51];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 47);
  c1_R2D = 57.295779513082323;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 50);
  c1_g = 9.81;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 51);
  c1_vs = 340.3;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 52);
  c1_R2D = 57.295779513082323;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 53);
  c1_rho = 1.225;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 54);
  c1_dt = 0.005;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 55);
  c1_m = 1177.0410005333333;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 58);
  c1_deltaA = c1_u[0];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 59);
  c1_deltaE = c1_u[1];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 60);
  c1_deltaR = c1_u[2];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 61);
  c1_throttle = c1_u[3];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 62);
  c1_dE = c1_deltaE * 57.295779513082323;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 63);
  c1_dA = c1_deltaA * 57.295779513082323;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 64);
  c1_dR = c1_deltaR * 57.295779513082323;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 66);
  c1_p = chartInstance->c1_states[3];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 67);
  c1_q = chartInstance->c1_states[4];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 68);
  c1_r = chartInstance->c1_states[5];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 72);
  c1_CX_dE = chartInstance->c1_states[6];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 74);
  c1_CY_dR = chartInstance->c1_states[7];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 75);
  c1_CY_dE = chartInstance->c1_states[8];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 77);
  c1_CZ_dE = chartInstance->c1_states[9];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 78);
  c1_CZ_dA = chartInstance->c1_states[10];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 80);
  c1_Cl_dA = chartInstance->c1_states[11];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 81);
  c1_Cl_dR = chartInstance->c1_states[12];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 82);
  c1_Cl_dE = chartInstance->c1_states[13];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 84);
  c1_Cm_dE = chartInstance->c1_states[14];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 85);
  c1_Cm_dA = chartInstance->c1_states[15];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 87);
  c1_Cn_dA = chartInstance->c1_states[16];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 88);
  c1_Cn_dR = chartInstance->c1_states[17];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 89);
  c1_Cn_dE = chartInstance->c1_states[18];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 91);
  c1_CX_dE1 = c1_CX_dE * 0.00095;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 92);
  c1_CX_dE2 = c1_CX_dE * 8.5E-7;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 94);
  c1_CY_dR1 = c1_CY_dR * 0.00155;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 95);
  c1_CY_dR2 = c1_CY_dR * 8.0E-6;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 96);
  c1_CY_dE1 = c1_CY_dE * 0.000175;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 98);
  c1_CZ_dE1 = c1_CZ_dE * 0.00476;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 99);
  c1_CZ_dE2 = c1_CZ_dE * 3.3E-5;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 100);
  c1_CZ_dA1 = c1_CZ_dA * 7.5E-5;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 102);
  c1_Cl_dA1 = c1_Cl_dA * 0.00061;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 103);
  c1_Cl_dA2 = c1_Cl_dA * 2.5E-5;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 104);
  c1_Cl_dA3 = c1_Cl_dA * 2.6E-6;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 105);
  c1_Cl_dR1 = c1_Cl_dR * -0.00023;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 106);
  c1_Cl_dR2 = c1_Cl_dR * 4.5E-6;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 107);
  c1_Cl_dE1 = c1_Cl_dE * 5.24E-5;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 109);
  c1_Cm_dE1 = c1_Cm_dE * 0.00654;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 110);
  c1_Cm_dE2 = c1_Cm_dE * 8.49E-5;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 111);
  c1_Cm_dE3 = c1_Cm_dE * 3.74E-6;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 112);
  c1_Cm_dA1 = c1_Cm_dA * 3.5E-5;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 114);
  c1_Cn_dA1 = c1_Cn_dA * 1.4E-5;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 115);
  c1_Cn_dA2 = c1_Cn_dA * 7.0E-6;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 116);
  c1_Cn_dR1 = c1_Cn_dR * 0.0009;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 117);
  c1_Cn_dR2 = c1_Cn_dR * 4.0E-6;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 118);
  c1_Cn_dE1 = c1_Cn_dE * 8.73E-5;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 119);
  c1_Cn_dE2 = c1_Cn_dE * 8.7E-6;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 122);
  c1_S = 20.0;
  _SFD_SYMBOL_SWITCH(56U, 56U);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 123);
  c1_m = 1177.0410005333333;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 124);
  c1_b = 6.666666666666667;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 125);
  c1_cbar = 3.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 126);
  c1_Ix = 2256.9839826075154;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, MAX_int8_T);
  c1_Iy = 11044.488299351713;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 128U);
  c1_Iz = 12636.21789221188;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 129U);
  c1_Ixz = 106.20569401537166;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 130U);
  c1_xCG_ref = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 131U);
  c1_xCG = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 134U);
  c1_qbar = 0.6125 * c1_mpower(chartInstance, c1_Vt);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 137U);
  c1_A = c1_H;
  c1_x = c1_A;
  c1_b_x = c1_x;
  c1_c_x = c1_b_x;
  c1_hT = c1_c_x / 3048.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 139U);
  c1_b_A = c1_Vt;
  c1_d_x = c1_b_A;
  c1_e_x = c1_d_x;
  c1_f_x = c1_e_x;
  c1_b_y = c1_f_x / 340.3;
  c1_c_A = c1_Vt;
  c1_g_x = c1_c_A;
  c1_h_x = c1_g_x;
  c1_i_x = c1_h_x;
  c1_c_y = c1_i_x / 340.3;
  c1_d_A = c1_Vt;
  c1_j_x = c1_d_A;
  c1_k_x = c1_j_x;
  c1_l_x = c1_k_x;
  c1_d_y = c1_l_x / 340.3;
  c1_e_A = c1_Vt;
  c1_m_x = c1_e_A;
  c1_n_x = c1_m_x;
  c1_o_x = c1_n_x;
  c1_e_y = c1_o_x / 340.3;
  c1_f_A = ((((((((30.21 - 0.668 * c1_hT) - 6.877 * c1_mpower(chartInstance,
    c1_hT)) + 1.951 * c1_b_mpower(chartInstance, c1_hT)) - 0.1512 * c1_c_mpower
                (chartInstance, c1_hT)) + c1_b_y * ((((-33.8 + 3.347 * c1_hT) +
    18.13 * c1_mpower(chartInstance, c1_hT)) - 5.865 * c1_b_mpower(chartInstance,
    c1_hT)) + 0.4757 * c1_c_mpower(chartInstance, c1_hT))) + c1_mpower
              (chartInstance, c1_c_y) * ((((100.8 - 77.56 * c1_hT) + 5.441 *
    c1_mpower(chartInstance, c1_hT)) + 2.864 * c1_b_mpower(chartInstance, c1_hT))
    - 0.3355 * c1_c_mpower(chartInstance, c1_hT))) + c1_b_mpower(chartInstance,
              c1_d_y) * ((((-78.99 + 101.4 * c1_hT) - 30.28 * c1_mpower
    (chartInstance, c1_hT)) + 3.236 * c1_b_mpower(chartInstance, c1_hT)) -
              0.1089 * c1_c_mpower(chartInstance, c1_hT))) + c1_c_mpower
            (chartInstance, c1_e_y) * ((((18.74 - 31.6 * c1_hT) + 12.04 *
    c1_mpower(chartInstance, c1_hT)) - 1.785 * c1_b_mpower(chartInstance, c1_hT))
             + 0.09417 * c1_c_mpower(chartInstance, c1_hT))) * 4448.22;
  c1_p_x = c1_f_A;
  c1_q_x = c1_p_x;
  c1_r_x = c1_q_x;
  c1_Tmax = c1_r_x / 20.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 145U);
  c1_T = c1_Tmax * c1_throttle;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 147U);
  c1_g_A = 180.0 * c1_q * 3.0;
  c1_s_x = c1_g_A;
  c1_t_x = c1_s_x;
  c1_u_x = c1_t_x;
  c1_f_y = c1_u_x / 3.1415926535897931;
  c1_h_A = c1_f_y;
  c1_v_x = c1_h_A;
  c1_w_x = c1_v_x;
  c1_x_x = c1_w_x;
  c1_g_y = c1_x_x / 2.0;
  c1_i_A = c1_g_y;
  c1_B = c1_Vt;
  c1_y_x = c1_i_A;
  c1_h_y = c1_B;
  c1_ab_x = c1_y_x;
  c1_i_y = c1_h_y;
  c1_bb_x = c1_ab_x;
  c1_j_y = c1_i_y;
  c1_k_y = c1_bb_x / c1_j_y;
  c1_CX = (((((-0.0434 + 0.00239 * c1_ALP) + 2.53E-5 * c1_mpower(chartInstance,
    c1_BET)) - 1.07E-6 * c1_ALP * c1_mpower(chartInstance, c1_BET)) + c1_CX_dE1 *
            c1_dE) - c1_CX_dE2 * c1_dE * c1_mpower(chartInstance, c1_BET)) +
    c1_k_y * ((0.00873 + 0.001 * c1_ALP) - 0.000175 * c1_mpower(chartInstance,
    c1_ALP));
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 148U);
  c1_b_B = c1_Vt;
  c1_l_y = c1_b_B;
  c1_m_y = c1_l_y;
  c1_n_y = c1_m_y;
  c1_o_y = 190.9859317102744 / c1_n_y;
  c1_CY = ((-0.012 * c1_BET + c1_CY_dR1 * c1_dR) - c1_CY_dR2 * c1_dR * c1_ALP) +
    c1_o_y * (((0.00225 * c1_p + 0.0117 * c1_r) - 0.000367 * c1_r * c1_ALP) +
              c1_CY_dE1 * c1_r * c1_dE);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 149U);
  c1_j_A = 180.0 * c1_q * 3.0;
  c1_cb_x = c1_j_A;
  c1_db_x = c1_cb_x;
  c1_eb_x = c1_db_x;
  c1_p_y = c1_eb_x / 3.1415926535897931;
  c1_k_A = c1_p_y;
  c1_fb_x = c1_k_A;
  c1_gb_x = c1_fb_x;
  c1_hb_x = c1_gb_x;
  c1_q_y = c1_hb_x / 2.0;
  c1_l_A = c1_q_y;
  c1_c_B = c1_Vt;
  c1_ib_x = c1_l_A;
  c1_r_y = c1_c_B;
  c1_jb_x = c1_ib_x;
  c1_s_y = c1_r_y;
  c1_kb_x = c1_jb_x;
  c1_t_y = c1_s_y;
  c1_u_y = c1_kb_x / c1_t_y;
  c1_CZ = ((((-0.131 - 0.0538 * c1_ALP) - c1_CZ_dE1 * c1_dE) - c1_CZ_dE2 * c1_dE
            * c1_ALP) - c1_CZ_dA1 * c1_power(chartInstance, c1_dA)) + c1_u_y *
    ((-0.111 + 0.00517 * c1_ALP) - 0.0011 * c1_mpower(chartInstance, c1_ALP));
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 150U);
  c1_d_B = c1_Vt;
  c1_v_y = c1_d_B;
  c1_w_y = c1_v_y;
  c1_x_y = c1_w_y;
  c1_y_y = 190.9859317102744 / c1_x_y;
  c1_Cl = ((((-0.000598 * c1_BET - 0.000283 * c1_ALP * c1_BET) + 1.51E-5 *
             c1_mpower(chartInstance, c1_ALP) * c1_BET) - c1_dA * ((c1_Cl_dA1 +
              c1_Cl_dA2 * c1_ALP) - c1_Cl_dA3 * c1_mpower(chartInstance, c1_ALP)))
           - c1_dR * (c1_Cl_dR1 + c1_Cl_dR2 * c1_ALP)) + c1_y_y * (((((-0.00412 *
    c1_p - 0.000524 * c1_p * c1_ALP) + 4.36E-5 * c1_p * c1_mpower(chartInstance,
    c1_ALP)) + 0.000436 * c1_r) + 0.000105 * c1_r * c1_ALP) + c1_Cl_dE1 * c1_r *
    c1_dE);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 151U);
  c1_m_A = 180.0 * c1_q * 3.0;
  c1_lb_x = c1_m_A;
  c1_mb_x = c1_lb_x;
  c1_nb_x = c1_mb_x;
  c1_ab_y = c1_nb_x / 2.0;
  c1_n_A = c1_ab_y;
  c1_ob_x = c1_n_A;
  c1_pb_x = c1_ob_x;
  c1_qb_x = c1_pb_x;
  c1_bb_y = c1_qb_x / 3.1415926535897931;
  c1_o_A = c1_bb_y;
  c1_e_B = c1_Vt;
  c1_rb_x = c1_o_A;
  c1_cb_y = c1_e_B;
  c1_sb_x = c1_rb_x;
  c1_db_y = c1_cb_y;
  c1_tb_x = c1_sb_x;
  c1_eb_y = c1_db_y;
  c1_fb_y = c1_tb_x / c1_eb_y;
  c1_Cm = ((((((((-0.00661 - 0.00267 * c1_ALP) - 6.48E-5 * c1_mpower
                 (chartInstance, c1_BET)) - 2.65E-6 * c1_ALP * c1_mpower
                (chartInstance, c1_BET)) - c1_Cm_dE1 * c1_dE) - c1_Cm_dE2 *
              c1_dE * c1_ALP) + c1_Cm_dE3 * c1_dE * c1_mpower(chartInstance,
              c1_BET)) - c1_Cm_dA1 * c1_power(chartInstance, c1_dA)) + c1_fb_y *
           (-0.0473 - 0.00157 * c1_ALP)) + 0.0 * c1_CZ;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 152U);
  c1_f_B = c1_Vt;
  c1_gb_y = c1_f_B;
  c1_hb_y = c1_gb_y;
  c1_ib_y = c1_hb_y;
  c1_jb_y = 190.9859317102744 / c1_ib_y;
  c1_Cn = ((((((0.00228 * c1_BET + 1.79E-6 * c1_b_mpower(chartInstance, c1_BET))
               + c1_Cn_dA1 * c1_dA) + c1_Cn_dA2 * c1_dA * c1_ALP) - c1_Cn_dR1 *
             c1_dR) + c1_Cn_dR2 * c1_dR * c1_ALP) + c1_jb_y * (((((-6.63E-5 *
    c1_p - 1.92E-5 * c1_p * c1_ALP) + 5.06E-6 * c1_p * c1_mpower(chartInstance,
    c1_ALP)) - 0.00606 * c1_r) - c1_Cn_dE1 * c1_r * c1_dE) + c1_Cn_dE2 * c1_r *
            c1_dE * c1_ALP)) - 0.0 * c1_CY;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 154U);
  c1_c1 = -0.70592099279383547;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 155U);
  c1_c2 = 0.014338034095370216;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 156U);
  c1_c3 = 0.000443244465804795;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 157U);
  c1_c4 = 3.7254094944251367E-6;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 158U);
  c1_c5 = 0.93976593829282273;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 159U);
  c1_c6 = 0.0096161715361322529;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 160U);
  c1_c7 = 9.054290003265229E-5;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 161U);
  c1_c8 = -0.69609284164731566;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 162U);
  c1_c9 = 7.916891495812398E-5;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 164U);
  c1_heng = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 165U);
  c1_pdot = (-0.70592099279383547 * c1_r + 0.014338034095370216 * c1_p) * c1_q +
    c1_qbar * 20.0 * 6.666666666666667 * (0.000443244465804795 * c1_Cl +
    3.7254094944251367E-6 * c1_Cn);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 166U);
  c1_qdot = (0.93976593829282273 * c1_p * c1_r - 0.0096161715361322529 *
             (c1_mpower(chartInstance, c1_p) - c1_mpower(chartInstance, c1_r)))
    + c1_qbar * 20.0 * 3.0 * 9.054290003265229E-5 * c1_Cm;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 167U);
  c1_rdot = (-0.69609284164731566 * c1_p - 0.014338034095370216 * c1_r) * c1_q +
    c1_qbar * 20.0 * 6.666666666666667 * (3.7254094944251367E-6 * c1_Cl +
    7.916891495812398E-5 * c1_Cn);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 170U);
  c1_p_A = c1_qbar * 20.0 * c1_CX + c1_T;
  c1_ub_x = c1_p_A;
  c1_vb_x = c1_ub_x;
  c1_wb_x = c1_vb_x;
  c1_kb_y = c1_wb_x / 1177.0410005333333;
  chartInstance->c1_states[0] = c1_kb_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 171U);
  c1_q_A = c1_qbar * 20.0 * c1_CY;
  c1_xb_x = c1_q_A;
  c1_yb_x = c1_xb_x;
  c1_ac_x = c1_yb_x;
  c1_lb_y = c1_ac_x / 1177.0410005333333;
  chartInstance->c1_states[1] = c1_lb_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 172U);
  c1_r_A = c1_qbar * 20.0 * c1_CZ;
  c1_bc_x = c1_r_A;
  c1_cc_x = c1_bc_x;
  c1_dc_x = c1_cc_x;
  c1_mb_y = c1_dc_x / 1177.0410005333333;
  chartInstance->c1_states[2] = c1_mb_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 175U);
  c1_hoistedGlobal = chartInstance->c1_prev_p;
  c1_s_A = 0.005 * (c1_hoistedGlobal + c1_pdot);
  c1_ec_x = c1_s_A;
  c1_fc_x = c1_ec_x;
  c1_gc_x = c1_fc_x;
  c1_nb_y = c1_gc_x / 2.0;
  c1_pNew = c1_p + c1_nb_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 176U);
  c1_b_hoistedGlobal = chartInstance->c1_prev_q;
  c1_t_A = 0.005 * (c1_b_hoistedGlobal + c1_qdot);
  c1_hc_x = c1_t_A;
  c1_ic_x = c1_hc_x;
  c1_jc_x = c1_ic_x;
  c1_ob_y = c1_jc_x / 2.0;
  c1_qNew = c1_q + c1_ob_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 177U);
  c1_c_hoistedGlobal = chartInstance->c1_prev_r;
  c1_u_A = 0.005 * (c1_c_hoistedGlobal + c1_rdot);
  c1_kc_x = c1_u_A;
  c1_lc_x = c1_kc_x;
  c1_mc_x = c1_lc_x;
  c1_pb_y = c1_mc_x / 2.0;
  c1_rNew = c1_r + c1_pb_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 179U);
  chartInstance->c1_prev_p = c1_pNew;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 180U);
  chartInstance->c1_prev_q = c1_qNew;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 181U);
  chartInstance->c1_prev_r = c1_rNew;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 183U);
  chartInstance->c1_states[3] = c1_pNew;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 184U);
  chartInstance->c1_states[4] = c1_qNew;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 185U);
  chartInstance->c1_states[5] = c1_rNew;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 187U);
  c1_F[0] = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 188U);
  c1_v_A = 1.4603343338198285 * c1_qbar * ((-0.000175 * c1_mpower(chartInstance,
    c1_ALP) + 0.001 * c1_ALP) + 0.00873);
  c1_g_B = c1_Vt;
  c1_nc_x = c1_v_A;
  c1_qb_y = c1_g_B;
  c1_oc_x = c1_nc_x;
  c1_rb_y = c1_qb_y;
  c1_pc_x = c1_oc_x;
  c1_sb_y = c1_rb_y;
  c1_tb_y = c1_pc_x / c1_sb_y;
  c1_F[76] = c1_tb_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 189U);
  c1_F[114] = 0.016991761536715992 * c1_qbar * (-8.5E-7 * c1_dE * c1_mpower
    (chartInstance, c1_BET) + 0.00095 * c1_dE);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 191U);
  c1_F[20] = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 192U);
  c1_w_A = 0.0073016716690991424 * c1_qbar;
  c1_h_B = c1_Vt;
  c1_qc_x = c1_w_A;
  c1_ub_y = c1_h_B;
  c1_rc_x = c1_qc_x;
  c1_vb_y = c1_ub_y;
  c1_sc_x = c1_rc_x;
  c1_wb_y = c1_vb_y;
  c1_xb_y = c1_sc_x / c1_wb_y;
  c1_F[58] = c1_xb_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 193U);
  c1_x_A = 3.2451874084885075 * c1_qbar * ((0.000175 * c1_CY_dE * c1_dE -
    0.000367 * c1_ALP) + 0.0117);
  c1_i_B = c1_Vt;
  c1_tc_x = c1_x_A;
  c1_yb_y = c1_i_B;
  c1_uc_x = c1_tc_x;
  c1_ac_y = c1_yb_y;
  c1_vc_x = c1_uc_x;
  c1_bc_y = c1_ac_y;
  c1_cc_y = c1_vc_x / c1_bc_y;
  c1_F[96] = c1_cc_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 194U);
  c1_F[134] = 0.016991761536715992 * c1_qbar * (0.00155 * c1_dR - 8.0E-6 *
    c1_ALP * c1_dR);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 195U);
  c1_y_A = 0.00056790779648548887 * c1_dE * c1_qbar * c1_r;
  c1_j_B = c1_Vt;
  c1_wc_x = c1_y_A;
  c1_dc_y = c1_j_B;
  c1_xc_x = c1_wc_x;
  c1_ec_y = c1_dc_y;
  c1_yc_x = c1_xc_x;
  c1_fc_y = c1_ec_y;
  c1_gc_y = c1_yc_x / c1_fc_y;
  c1_F[153] = c1_gc_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 197U);
  c1_F[40] = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 198U);
  c1_ab_A = -(1.4603343338198285 * c1_qbar * ((0.0011 * c1_mpower(chartInstance,
    c1_ALP) - 0.00517 * c1_ALP) + 0.111));
  c1_k_B = c1_Vt;
  c1_ad_x = c1_ab_A;
  c1_hc_y = c1_k_B;
  c1_bd_x = c1_ad_x;
  c1_ic_y = c1_hc_y;
  c1_cd_x = c1_bd_x;
  c1_jc_y = c1_ic_y;
  c1_kc_y = c1_cd_x / c1_jc_y;
  c1_F[78] = c1_kc_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 199U);
  c1_F[173] = -0.016991761536715992 * c1_qbar * (0.00476 * c1_dE + 3.3E-5 *
    c1_ALP * c1_dE);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 200U);
  c1_F[192] = -1.2743821152536993E-6 * c1_mpower(chartInstance, c1_dA) * c1_qbar;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 202U);
  c1_bb_A = 0.084653457277151636 * ((-4.36E-5 * c1_mpower(chartInstance, c1_ALP)
    + 0.000524 * c1_ALP) + 0.00412);
  c1_l_B = c1_Vt;
  c1_dd_x = c1_bb_A;
  c1_lc_y = c1_l_B;
  c1_ed_x = c1_dd_x;
  c1_mc_y = c1_lc_y;
  c1_fd_x = c1_ed_x;
  c1_nc_y = c1_mc_y;
  c1_oc_y = c1_fd_x / c1_nc_y;
  c1_cb_A = 0.000711500803295087 * ((-5.06E-6 * c1_mpower(chartInstance, c1_ALP)
    + 1.92E-5 * c1_ALP) + 6.63E-5);
  c1_m_B = c1_Vt;
  c1_gd_x = c1_cb_A;
  c1_pc_y = c1_m_B;
  c1_hd_x = c1_gd_x;
  c1_qc_y = c1_pc_y;
  c1_id_x = c1_hd_x;
  c1_rc_y = c1_qc_y;
  c1_sc_y = c1_id_x / c1_rc_y;
  c1_F[60] = 0.0025 * (0.014338034095370216 * c1_q - 133.33333333333334 *
                       c1_qbar * (c1_oc_y + c1_sc_y)) + 1.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 203U);
  c1_F[79] = 0.0025 * (0.014338034095370216 * c1_p - 0.70592099279383547 * c1_r);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 204U);
  c1_db_A = 0.000711500803295087 * ((8.73E-5 * c1_Cn_dE * c1_dE - 8.7E-6 *
    c1_ALP * c1_Cn_dE * c1_dE) + 0.00606);
  c1_n_B = c1_Vt;
  c1_jd_x = c1_db_A;
  c1_tc_y = c1_n_B;
  c1_kd_x = c1_jd_x;
  c1_uc_y = c1_tc_y;
  c1_ld_x = c1_kd_x;
  c1_vc_y = c1_uc_y;
  c1_wc_y = c1_ld_x / c1_vc_y;
  c1_eb_A = 0.084653457277151636 * ((0.000105 * c1_ALP + 5.24E-5 * c1_Cl_dE *
    c1_dE) + 0.000436);
  c1_o_B = c1_Vt;
  c1_md_x = c1_eb_A;
  c1_xc_y = c1_o_B;
  c1_nd_x = c1_md_x;
  c1_yc_y = c1_xc_y;
  c1_od_x = c1_nd_x;
  c1_ad_y = c1_yc_y;
  c1_bd_y = c1_od_x / c1_ad_y;
  c1_F[98] = -0.0025 * (0.70592099279383547 * c1_q + 133.33333333333334 *
                        c1_qbar * (c1_wc_y - c1_bd_y));
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 205U);
  c1_F[212] = -0.029549631053653 * c1_dA * 0.005 * c1_qbar * ((-2.6E-6 *
    c1_mpower(chartInstance, c1_ALP) + 2.5E-5 * c1_ALP) + 0.00061);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 206U);
  c1_F[231] = -0.029549631053653 * c1_dR * 0.005 * c1_qbar * (4.5E-6 * c1_ALP -
    0.00023);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 207U);
  c1_fb_A = 0.00029572274408818305 * c1_dE * 0.005 * c1_qbar * c1_r;
  c1_p_B = c1_Vt;
  c1_pd_x = c1_fb_A;
  c1_cd_y = c1_p_B;
  c1_qd_x = c1_pd_x;
  c1_dd_y = c1_cd_y;
  c1_rd_x = c1_qd_x;
  c1_ed_y = c1_dd_y;
  c1_fd_y = c1_rd_x / c1_ed_y;
  c1_F[250] = c1_fd_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 208U);
  c1_F[307] = 0.33333333333333337 * c1_qbar * (5.2155732921951913E-11 * c1_dA +
    2.6077866460975956E-11 * c1_ALP * c1_dA);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 209U);
  c1_F[326] = -0.33333333333333337 * c1_qbar * (3.3528685449826229E-9 * c1_dR -
    1.4901637977700546E-11 * c1_ALP * c1_dR);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 210U);
  c1_gb_A = -(0.00023716693443169568 * c1_qbar * (8.73E-5 * c1_dE * c1_r -
    8.7E-6 * c1_ALP * c1_dE * c1_r));
  c1_q_B = c1_Vt;
  c1_sd_x = c1_gb_A;
  c1_gd_y = c1_q_B;
  c1_td_x = c1_sd_x;
  c1_hd_y = c1_gd_y;
  c1_ud_x = c1_td_x;
  c1_id_y = c1_hd_y;
  c1_jd_y = c1_ud_x / c1_id_y;
  c1_F[345] = c1_jd_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 212U);
  c1_F[61] = -0.0025 * (0.019232343072264506 * c1_p - 0.93976593829282262 * c1_r);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 213U);
  c1_hb_A = 0.0011672383582678274 * c1_qbar * (0.00157 * c1_ALP + 0.0473);
  c1_r_B = c1_Vt;
  c1_vd_x = c1_hb_A;
  c1_kd_y = c1_r_B;
  c1_wd_x = c1_vd_x;
  c1_ld_y = c1_kd_y;
  c1_xd_x = c1_wd_x;
  c1_md_y = c1_ld_y;
  c1_nd_y = c1_xd_x / c1_md_y;
  c1_F[80] = 1.0 - c1_nd_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 214U);
  c1_F[99] = 0.0025 * (0.93976593829282262 * c1_p + 0.019232343072264506 * c1_r);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 215U);
  c1_F[270] = -1.3581435004897844E-5 * c1_qbar * ((-3.74E-6 * c1_dE * c1_mpower
    (chartInstance, c1_BET) + 0.00654 * c1_dE) + 8.49E-5 * c1_ALP * c1_dE);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 216U);
  c1_F[289] = -9.50700450342849E-8 * c1_mpower(chartInstance, c1_dA) * 0.005 *
    c1_qbar;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 218U);
  c1_ib_A = 0.000711500803295087 * ((-4.36E-5 * c1_mpower(chartInstance, c1_ALP)
    + 0.000524 * c1_ALP) + 0.00412);
  c1_s_B = c1_Vt;
  c1_yd_x = c1_ib_A;
  c1_od_y = c1_s_B;
  c1_ae_x = c1_yd_x;
  c1_pd_y = c1_od_y;
  c1_be_x = c1_ae_x;
  c1_qd_y = c1_pd_y;
  c1_rd_y = c1_be_x / c1_qd_y;
  c1_jb_A = 0.015120148985768788 * ((-5.06E-6 * c1_mpower(chartInstance, c1_ALP)
    + 1.92E-5 * c1_ALP) + 6.63E-5);
  c1_t_B = c1_Vt;
  c1_ce_x = c1_jb_A;
  c1_sd_y = c1_t_B;
  c1_de_x = c1_ce_x;
  c1_td_y = c1_sd_y;
  c1_ee_x = c1_de_x;
  c1_ud_y = c1_td_y;
  c1_vd_y = c1_ee_x / c1_ud_y;
  c1_F[62] = -0.0025 * (0.69609284164731566 * c1_q + 133.33333333333334 *
                        c1_qbar * (c1_rd_y + c1_vd_y));
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 219U);
  c1_F[81] = -0.0025 * (0.69609284164731566 * c1_p + 0.014338034095370216 * c1_r);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 220U);
  c1_kb_A = 0.015120148985768788 * ((8.73E-5 * c1_Cn_dE * c1_dE - 8.7E-6 *
    c1_ALP * c1_Cn_dE * c1_dE) + 0.00606);
  c1_u_B = c1_Vt;
  c1_fe_x = c1_kb_A;
  c1_wd_y = c1_u_B;
  c1_ge_x = c1_fe_x;
  c1_xd_y = c1_wd_y;
  c1_he_x = c1_ge_x;
  c1_yd_y = c1_xd_y;
  c1_ae_y = c1_he_x / c1_yd_y;
  c1_lb_A = 0.000711500803295087 * ((0.000105 * c1_ALP + 5.24E-5 * c1_Cl_dE *
    c1_dE) + 0.000436);
  c1_v_B = c1_Vt;
  c1_ie_x = c1_lb_A;
  c1_be_y = c1_v_B;
  c1_je_x = c1_ie_x;
  c1_ce_y = c1_be_y;
  c1_ke_x = c1_je_x;
  c1_de_y = c1_ce_y;
  c1_ee_y = c1_ke_x / c1_de_y;
  c1_F[100] = 1.0 - 0.0025 * (0.014338034095370216 * c1_q + 133.33333333333334 *
    c1_qbar * (c1_ae_y - c1_ee_y));
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 221U);
  c1_F[214] = -0.00024836063296167579 * c1_dA * 0.005 * c1_qbar * ((-2.6E-6 *
    c1_mpower(chartInstance, c1_ALP) + 2.5E-5 * c1_ALP) + 0.00061);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 222U);
  c1_F[233] = -0.00024836063296167579 * c1_dR * 0.005 * c1_qbar * (4.5E-6 *
    c1_ALP - 0.00023);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 223U);
  c1_mb_A = 2.4855094728441706E-6 * c1_dE * 0.005 * c1_qbar * c1_r;
  c1_w_B = c1_Vt;
  c1_le_x = c1_mb_A;
  c1_fe_y = c1_w_B;
  c1_me_x = c1_le_x;
  c1_ge_y = c1_fe_y;
  c1_ne_x = c1_me_x;
  c1_he_y = c1_ge_y;
  c1_ie_y = c1_ne_x / c1_he_y;
  c1_F[252] = c1_ie_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 224U);
  c1_F[309] = 0.33333333333333337 * c1_qbar * (1.1083648094137358E-9 * c1_dA +
    5.5418240470686788E-10 * c1_ALP * c1_dA);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 225U);
  c1_F[328] = -0.33333333333333337 * c1_qbar * (7.1252023462311588E-8 * c1_dR -
    3.1667565983249591E-10 * c1_ALP * c1_dR);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 226U);
  c1_nb_A = -(0.00504004966192293 * c1_qbar * (8.73E-5 * c1_dE * c1_r - 8.7E-6 *
    c1_ALP * c1_dE * c1_r));
  c1_x_B = c1_Vt;
  c1_oe_x = c1_nb_A;
  c1_je_y = c1_x_B;
  c1_pe_x = c1_oe_x;
  c1_ke_y = c1_je_y;
  c1_qe_x = c1_pe_x;
  c1_le_y = c1_ke_y;
  c1_me_y = c1_qe_x / c1_le_y;
  c1_F[347] = c1_me_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 228U);
  for (c1_i52 = 0; c1_i52 < 361; c1_i52++) {
    c1_d_hoistedGlobal[c1_i52] = chartInstance->c1_cov[c1_i52];
  }

  for (c1_i53 = 0; c1_i53 < 361; c1_i53++) {
    c1_b_a[c1_i53] = c1_F[c1_i53];
  }

  c1_b_eml_scalar_eg(chartInstance);
  c1_b_eml_scalar_eg(chartInstance);
  for (c1_i54 = 0; c1_i54 < 361; c1_i54++) {
    c1_ne_y[c1_i54] = 0.0;
  }

  for (c1_i55 = 0; c1_i55 < 361; c1_i55++) {
    c1_c_a[c1_i55] = c1_b_a[c1_i55];
  }

  for (c1_i56 = 0; c1_i56 < 361; c1_i56++) {
    c1_e_hoistedGlobal[c1_i56] = c1_d_hoistedGlobal[c1_i56];
  }

  c1_g_eml_xgemm(chartInstance, c1_c_a, c1_e_hoistedGlobal, c1_ne_y);
  c1_i57 = 0;
  for (c1_i58 = 0; c1_i58 < 19; c1_i58++) {
    c1_i59 = 0;
    for (c1_i60 = 0; c1_i60 < 19; c1_i60++) {
      c1_d_hoistedGlobal[c1_i60 + c1_i57] = c1_F[c1_i59 + c1_i58];
      c1_i59 += 19;
    }

    c1_i57 += 19;
  }

  c1_b_eml_scalar_eg(chartInstance);
  c1_b_eml_scalar_eg(chartInstance);
  for (c1_i61 = 0; c1_i61 < 361; c1_i61++) {
    c1_b_a[c1_i61] = 0.0;
  }

  for (c1_i62 = 0; c1_i62 < 361; c1_i62++) {
    c1_oe_y[c1_i62] = c1_ne_y[c1_i62];
  }

  for (c1_i63 = 0; c1_i63 < 361; c1_i63++) {
    c1_f_hoistedGlobal[c1_i63] = c1_d_hoistedGlobal[c1_i63];
  }

  c1_g_eml_xgemm(chartInstance, c1_oe_y, c1_f_hoistedGlobal, c1_b_a);
  for (c1_i64 = 0; c1_i64 < 361; c1_i64++) {
    chartInstance->c1_cov[c1_i64] = c1_Q[c1_i64] + c1_b_a[c1_i64];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 231U);
  for (c1_i65 = 0; c1_i65 < 114; c1_i65++) {
    c1_b_H[c1_i65] = c1_d_a[c1_i65];
  }

  _SFD_SYMBOL_SWITCH(92U, 92U);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 232U);
  for (c1_i66 = 0; c1_i66 < 361; c1_i66++) {
    c1_d_hoistedGlobal[c1_i66] = chartInstance->c1_cov[c1_i66];
  }

  c1_c_eml_scalar_eg(chartInstance);
  c1_c_eml_scalar_eg(chartInstance);
  for (c1_i67 = 0; c1_i67 < 114; c1_i67++) {
    c1_pe_y[c1_i67] = 0.0;
  }

  for (c1_i68 = 0; c1_i68 < 114; c1_i68++) {
    c1_e_a[c1_i68] = c1_d_a[c1_i68];
  }

  for (c1_i69 = 0; c1_i69 < 361; c1_i69++) {
    c1_g_hoistedGlobal[c1_i69] = c1_d_hoistedGlobal[c1_i69];
  }

  c1_h_eml_xgemm(chartInstance, c1_e_a, c1_g_hoistedGlobal, c1_pe_y);
  c1_d_eml_scalar_eg(chartInstance);
  c1_d_eml_scalar_eg(chartInstance);
  for (c1_i70 = 0; c1_i70 < 36; c1_i70++) {
    c1_qe_y[c1_i70] = 0.0;
  }

  for (c1_i71 = 0; c1_i71 < 114; c1_i71++) {
    c1_re_y[c1_i71] = c1_pe_y[c1_i71];
  }

  for (c1_i72 = 0; c1_i72 < 114; c1_i72++) {
    c1_c_b[c1_i72] = c1_b_b[c1_i72];
  }

  c1_i_eml_xgemm(chartInstance, c1_re_y, c1_c_b, c1_qe_y);
  for (c1_i73 = 0; c1_i73 < 36; c1_i73++) {
    c1_b_S[c1_i73] = c1_qe_y[c1_i73] + c1_R[c1_i73];
  }

  _SFD_SYMBOL_SWITCH(56U, 93U);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 233U);
  for (c1_i74 = 0; c1_i74 < 19; c1_i74++) {
    c1_h_hoistedGlobal[c1_i74] = chartInstance->c1_states[c1_i74];
  }

  c1_e_eml_scalar_eg(chartInstance);
  c1_e_eml_scalar_eg(chartInstance);
  c1_threshold(chartInstance);
  for (c1_i75 = 0; c1_i75 < 6; c1_i75++) {
    c1_se_y[c1_i75] = 0.0;
    c1_i76 = 0;
    for (c1_i77 = 0; c1_i77 < 19; c1_i77++) {
      c1_se_y[c1_i75] += c1_d_a[c1_i76 + c1_i75] * c1_h_hoistedGlobal[c1_i77];
      c1_i76 += 6;
    }
  }

  for (c1_i78 = 0; c1_i78 < 3; c1_i78++) {
    c1_b_accelerations[c1_i78] = c1_accelerations[c1_i78];
  }

  for (c1_i79 = 0; c1_i79 < 3; c1_i79++) {
    c1_b_accelerations[c1_i79 + 3] = c1_omega[c1_i79];
  }

  for (c1_i80 = 0; c1_i80 < 6; c1_i80++) {
    c1_nu[c1_i80] = c1_b_accelerations[c1_i80] - c1_se_y[c1_i80];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 234U);
  for (c1_i81 = 0; c1_i81 < 361; c1_i81++) {
    c1_d_hoistedGlobal[c1_i81] = chartInstance->c1_cov[c1_i81];
  }

  c1_f_eml_scalar_eg(chartInstance);
  c1_f_eml_scalar_eg(chartInstance);
  for (c1_i82 = 0; c1_i82 < 114; c1_i82++) {
    c1_te_y[c1_i82] = 0.0;
  }

  for (c1_i83 = 0; c1_i83 < 361; c1_i83++) {
    c1_i_hoistedGlobal[c1_i83] = c1_d_hoistedGlobal[c1_i83];
  }

  for (c1_i84 = 0; c1_i84 < 114; c1_i84++) {
    c1_d_b[c1_i84] = c1_b_b[c1_i84];
  }

  c1_j_eml_xgemm(chartInstance, c1_i_hoistedGlobal, c1_d_b, c1_te_y);
  for (c1_i85 = 0; c1_i85 < 36; c1_i85++) {
    c1_c_S[c1_i85] = c1_b_S[c1_i85];
  }

  c1_inv(chartInstance, c1_c_S, c1_qe_y);
  c1_g_eml_scalar_eg(chartInstance);
  c1_g_eml_scalar_eg(chartInstance);
  for (c1_i86 = 0; c1_i86 < 114; c1_i86++) {
    c1_K[c1_i86] = 0.0;
  }

  for (c1_i87 = 0; c1_i87 < 114; c1_i87++) {
    c1_K[c1_i87] = 0.0;
  }

  for (c1_i88 = 0; c1_i88 < 114; c1_i88++) {
    c1_dv11[c1_i88] = c1_te_y[c1_i88];
  }

  for (c1_i89 = 0; c1_i89 < 36; c1_i89++) {
    c1_dv12[c1_i89] = c1_qe_y[c1_i89];
  }

  for (c1_i90 = 0; c1_i90 < 114; c1_i90++) {
    c1_dv13[c1_i90] = c1_dv11[c1_i90];
  }

  for (c1_i91 = 0; c1_i91 < 36; c1_i91++) {
    c1_dv14[c1_i91] = c1_dv12[c1_i91];
  }

  c1_k_eml_xgemm(chartInstance, c1_dv13, c1_dv14, c1_K);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 235U);
  for (c1_i92 = 0; c1_i92 < 19; c1_i92++) {
    c1_h_hoistedGlobal[c1_i92] = chartInstance->c1_states[c1_i92];
  }

  for (c1_i93 = 0; c1_i93 < 114; c1_i93++) {
    c1_f_a[c1_i93] = c1_K[c1_i93];
  }

  for (c1_i94 = 0; c1_i94 < 6; c1_i94++) {
    c1_se_y[c1_i94] = c1_nu[c1_i94];
  }

  c1_h_eml_scalar_eg(chartInstance);
  c1_h_eml_scalar_eg(chartInstance);
  c1_threshold(chartInstance);
  for (c1_i95 = 0; c1_i95 < 19; c1_i95++) {
    c1_ue_y[c1_i95] = 0.0;
    c1_i96 = 0;
    for (c1_i97 = 0; c1_i97 < 6; c1_i97++) {
      c1_ue_y[c1_i95] += c1_f_a[c1_i96 + c1_i95] * c1_se_y[c1_i97];
      c1_i96 += 19;
    }
  }

  for (c1_i98 = 0; c1_i98 < 19; c1_i98++) {
    chartInstance->c1_states[c1_i98] = c1_h_hoistedGlobal[c1_i98] +
      c1_ue_y[c1_i98];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 236U);
  for (c1_i99 = 0; c1_i99 < 361; c1_i99++) {
    c1_d_hoistedGlobal[c1_i99] = chartInstance->c1_cov[c1_i99];
  }

  for (c1_i100 = 0; c1_i100 < 114; c1_i100++) {
    c1_f_a[c1_i100] = c1_K[c1_i100];
  }

  for (c1_i101 = 0; c1_i101 < 36; c1_i101++) {
    c1_qe_y[c1_i101] = c1_b_S[c1_i101];
  }

  c1_g_eml_scalar_eg(chartInstance);
  c1_g_eml_scalar_eg(chartInstance);
  for (c1_i102 = 0; c1_i102 < 114; c1_i102++) {
    c1_te_y[c1_i102] = 0.0;
  }

  for (c1_i103 = 0; c1_i103 < 114; c1_i103++) {
    c1_g_a[c1_i103] = c1_f_a[c1_i103];
  }

  for (c1_i104 = 0; c1_i104 < 36; c1_i104++) {
    c1_ve_y[c1_i104] = c1_qe_y[c1_i104];
  }

  c1_k_eml_xgemm(chartInstance, c1_g_a, c1_ve_y, c1_te_y);
  c1_i105 = 0;
  for (c1_i106 = 0; c1_i106 < 19; c1_i106++) {
    c1_i107 = 0;
    for (c1_i108 = 0; c1_i108 < 6; c1_i108++) {
      c1_pe_y[c1_i108 + c1_i105] = c1_K[c1_i107 + c1_i106];
      c1_i107 += 19;
    }

    c1_i105 += 6;
  }

  c1_i_eml_scalar_eg(chartInstance);
  c1_i_eml_scalar_eg(chartInstance);
  for (c1_i109 = 0; c1_i109 < 361; c1_i109++) {
    c1_ne_y[c1_i109] = 0.0;
  }

  for (c1_i110 = 0; c1_i110 < 114; c1_i110++) {
    c1_we_y[c1_i110] = c1_te_y[c1_i110];
  }

  for (c1_i111 = 0; c1_i111 < 114; c1_i111++) {
    c1_xe_y[c1_i111] = c1_pe_y[c1_i111];
  }

  c1_l_eml_xgemm(chartInstance, c1_we_y, c1_xe_y, c1_ne_y);
  for (c1_i112 = 0; c1_i112 < 361; c1_i112++) {
    chartInstance->c1_cov[c1_i112] = c1_d_hoistedGlobal[c1_i112] -
      c1_ne_y[c1_i112];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 238U);
  for (c1_i113 = 0; c1_i113 < 19; c1_i113++) {
    c1_states_OUT[c1_i113] = chartInstance->c1_states[c1_i113];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 239U);
  for (c1_i114 = 0; c1_i114 < 361; c1_i114++) {
    c1_dv15[c1_i114] = chartInstance->c1_cov[c1_i114];
  }

  c1_diag(chartInstance, c1_dv15, c1_dv16);
  for (c1_i115 = 0; c1_i115 < 19; c1_i115++) {
    c1_cov_OUT[c1_i115] = c1_dv16[c1_i115];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 240U);
  for (c1_i116 = 0; c1_i116 < 36; c1_i116++) {
    c1_d_S[c1_i116] = c1_b_S[c1_i116];
  }

  c1_b_diag(chartInstance, c1_d_S, c1_dv17);
  for (c1_i117 = 0; c1_i117 < 6; c1_i117++) {
    c1_S_OUT[c1_i117] = c1_dv17[c1_i117];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, -240);
  _SFD_SYMBOL_SCOPE_POP();
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber)
{
  (void)c1_machineNumber;
  _SFD_SCRIPT_TRANSLATION(c1_chartNumber, c1_instanceNumber, 0U,
    sf_debug_get_script_id(
    "C:\\Users\\Rudaba\\Documents\\PHD TAKE 2\\Simulations\\AircraftModelling\\simulateEKF_smallerStateVec.m"));
}

static void c1_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_sprintf, const char_T *c1_identifier, char_T c1_y[14])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_sprintf), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_sprintf);
}

static void c1_b_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y[14])
{
  char_T c1_cv0[14];
  int32_T c1_i118;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_cv0, 1, 10, 0U, 1, 0U, 2, 1,
                14);
  for (c1_i118 = 0; c1_i118 < 14; c1_i118++) {
    c1_y[c1_i118] = c1_cv0[c1_i118];
  }

  sf_mex_destroy(&c1_u);
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i119;
  real_T c1_b_inData[6];
  int32_T c1_i120;
  real_T c1_u[6];
  const mxArray *c1_y = NULL;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i119 = 0; c1_i119 < 6; c1_i119++) {
    c1_b_inData[c1_i119] = (*(real_T (*)[6])c1_inData)[c1_i119];
  }

  for (c1_i120 = 0; c1_i120 < 6; c1_i120++) {
    c1_u[c1_i120] = c1_b_inData[c1_i120];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 6), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_c_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_S_OUT, const char_T *c1_identifier, real_T c1_y[6])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_S_OUT), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_S_OUT);
}

static void c1_d_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[6])
{
  real_T c1_dv18[6];
  int32_T c1_i121;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv18, 1, 0, 0U, 1, 0U, 1, 6);
  for (c1_i121 = 0; c1_i121 < 6; c1_i121++) {
    c1_y[c1_i121] = c1_dv18[c1_i121];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_S_OUT;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[6];
  int32_T c1_i122;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_S_OUT = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_S_OUT), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_S_OUT);
  for (c1_i122 = 0; c1_i122 < 6; c1_i122++) {
    (*(real_T (*)[6])c1_outData)[c1_i122] = c1_y[c1_i122];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i123;
  real_T c1_b_inData[19];
  int32_T c1_i124;
  real_T c1_u[19];
  const mxArray *c1_y = NULL;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i123 = 0; c1_i123 < 19; c1_i123++) {
    c1_b_inData[c1_i123] = (*(real_T (*)[19])c1_inData)[c1_i123];
  }

  for (c1_i124 = 0; c1_i124 < 19; c1_i124++) {
    c1_u[c1_i124] = c1_b_inData[c1_i124];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 19), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_e_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_cov_OUT, const char_T *c1_identifier, real_T c1_y[19])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_cov_OUT), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_cov_OUT);
}

static void c1_f_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[19])
{
  real_T c1_dv19[19];
  int32_T c1_i125;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv19, 1, 0, 0U, 1, 0U, 1, 19);
  for (c1_i125 = 0; c1_i125 < 19; c1_i125++) {
    c1_y[c1_i125] = c1_dv19[c1_i125];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_cov_OUT;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[19];
  int32_T c1_i126;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_cov_OUT = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_cov_OUT), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_cov_OUT);
  for (c1_i126 = 0; c1_i126 < 19; c1_i126++) {
    (*(real_T (*)[19])c1_outData)[c1_i126] = c1_y[c1_i126];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i127;
  real_T c1_b_inData[4];
  int32_T c1_i128;
  real_T c1_u[4];
  const mxArray *c1_y = NULL;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i127 = 0; c1_i127 < 4; c1_i127++) {
    c1_b_inData[c1_i127] = (*(real_T (*)[4])c1_inData)[c1_i127];
  }

  for (c1_i128 = 0; c1_i128 < 4; c1_i128++) {
    c1_u[c1_i128] = c1_b_inData[c1_i128];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 4), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i129;
  real_T c1_b_inData[3];
  int32_T c1_i130;
  real_T c1_u[3];
  const mxArray *c1_y = NULL;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i129 = 0; c1_i129 < 3; c1_i129++) {
    c1_b_inData[c1_i129] = (*(real_T (*)[3])c1_inData)[c1_i129];
  }

  for (c1_i130 = 0; c1_i130 < 3; c1_i130++) {
    c1_u[c1_i130] = c1_b_inData[c1_i130];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_g_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_nargout;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_nargout = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nargout), &c1_thisId);
  sf_mex_destroy(&c1_nargout);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  if (!chartInstance->c1_prev_r_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_h_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_b_prev_r, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_prev_r),
    &c1_thisId);
  sf_mex_destroy(&c1_b_prev_r);
  return c1_y;
}

static real_T c1_i_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d1;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_prev_r_not_empty = false;
  } else {
    chartInstance->c1_prev_r_not_empty = true;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d1, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d1;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_prev_r;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_b_prev_r = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_prev_r),
    &c1_thisId);
  sf_mex_destroy(&c1_b_prev_r);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  if (!chartInstance->c1_prev_q_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_j_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_b_prev_q, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_prev_q),
    &c1_thisId);
  sf_mex_destroy(&c1_b_prev_q);
  return c1_y;
}

static real_T c1_k_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d2;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_prev_q_not_empty = false;
  } else {
    chartInstance->c1_prev_q_not_empty = true;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d2, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d2;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_prev_q;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_b_prev_q = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_prev_q),
    &c1_thisId);
  sf_mex_destroy(&c1_b_prev_q);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  if (!chartInstance->c1_prev_p_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_l_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_b_prev_p, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_prev_p),
    &c1_thisId);
  sf_mex_destroy(&c1_b_prev_p);
  return c1_y;
}

static real_T c1_m_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d3;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_prev_p_not_empty = false;
  } else {
    chartInstance->c1_prev_p_not_empty = true;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d3, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d3;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_prev_p;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_b_prev_p = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_prev_p),
    &c1_thisId);
  sf_mex_destroy(&c1_b_prev_p);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i131;
  int32_T c1_i132;
  int32_T c1_i133;
  real_T c1_b_inData[361];
  int32_T c1_i134;
  int32_T c1_i135;
  int32_T c1_i136;
  real_T c1_u[361];
  const mxArray *c1_y = NULL;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i131 = 0;
  for (c1_i132 = 0; c1_i132 < 19; c1_i132++) {
    for (c1_i133 = 0; c1_i133 < 19; c1_i133++) {
      c1_b_inData[c1_i133 + c1_i131] = (*(real_T (*)[361])c1_inData)[c1_i133 +
        c1_i131];
    }

    c1_i131 += 19;
  }

  c1_i134 = 0;
  for (c1_i135 = 0; c1_i135 < 19; c1_i135++) {
    for (c1_i136 = 0; c1_i136 < 19; c1_i136++) {
      c1_u[c1_i136 + c1_i134] = c1_b_inData[c1_i136 + c1_i134];
    }

    c1_i134 += 19;
  }

  c1_y = NULL;
  if (!chartInstance->c1_cov_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 19, 19),
                  false);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_n_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_b_cov, const char_T *c1_identifier, real_T c1_y[361])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_cov), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_cov);
}

static void c1_o_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[361])
{
  real_T c1_dv20[361];
  int32_T c1_i137;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_cov_not_empty = false;
  } else {
    chartInstance->c1_cov_not_empty = true;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv20, 1, 0, 0U, 1, 0U, 2, 19,
                  19);
    for (c1_i137 = 0; c1_i137 < 361; c1_i137++) {
      c1_y[c1_i137] = c1_dv20[c1_i137];
    }
  }

  sf_mex_destroy(&c1_u);
}

static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_cov;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[361];
  int32_T c1_i138;
  int32_T c1_i139;
  int32_T c1_i140;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_b_cov = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_cov), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_cov);
  c1_i138 = 0;
  for (c1_i139 = 0; c1_i139 < 19; c1_i139++) {
    for (c1_i140 = 0; c1_i140 < 19; c1_i140++) {
      (*(real_T (*)[361])c1_outData)[c1_i140 + c1_i138] = c1_y[c1_i140 + c1_i138];
    }

    c1_i138 += 19;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_j_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i141;
  real_T c1_b_inData[19];
  int32_T c1_i142;
  real_T c1_u[19];
  const mxArray *c1_y = NULL;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i141 = 0; c1_i141 < 19; c1_i141++) {
    c1_b_inData[c1_i141] = (*(real_T (*)[19])c1_inData)[c1_i141];
  }

  for (c1_i142 = 0; c1_i142 < 19; c1_i142++) {
    c1_u[c1_i142] = c1_b_inData[c1_i142];
  }

  c1_y = NULL;
  if (!chartInstance->c1_states_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 19), false);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_p_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_b_states, const char_T *c1_identifier, real_T c1_y[19])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_states), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_states);
}

static void c1_q_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[19])
{
  real_T c1_dv21[19];
  int32_T c1_i143;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_states_not_empty = false;
  } else {
    chartInstance->c1_states_not_empty = true;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv21, 1, 0, 0U, 1, 0U, 1, 19);
    for (c1_i143 = 0; c1_i143 < 19; c1_i143++) {
      c1_y[c1_i143] = c1_dv21[c1_i143];
    }
  }

  sf_mex_destroy(&c1_u);
}

static void c1_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_states;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[19];
  int32_T c1_i144;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_b_states = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_states), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_states);
  for (c1_i144 = 0; c1_i144 < 19; c1_i144++) {
    (*(real_T (*)[19])c1_outData)[c1_i144] = c1_y[c1_i144];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static void c1_r_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[4])
{
  real_T c1_dv22[4];
  int32_T c1_i145;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv22, 1, 0, 0U, 1, 0U, 1, 4);
  for (c1_i145 = 0; c1_i145 < 4; c1_i145++) {
    c1_y[c1_i145] = c1_dv22[c1_i145];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_u;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[4];
  int32_T c1_i146;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_u = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_u), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_u);
  for (c1_i146 = 0; c1_i146 < 4; c1_i146++) {
    (*(real_T (*)[4])c1_outData)[c1_i146] = c1_y[c1_i146];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static void c1_s_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[3])
{
  real_T c1_dv23[3];
  int32_T c1_i147;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv23, 1, 0, 0U, 1, 0U, 1, 3);
  for (c1_i147 = 0; c1_i147 < 3; c1_i147++) {
    c1_y[c1_i147] = c1_dv23[c1_i147];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_omega;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[3];
  int32_T c1_i148;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_omega = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_s_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_omega), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_omega);
  for (c1_i148 = 0; c1_i148 < 3; c1_i148++) {
    (*(real_T (*)[3])c1_outData)[c1_i148] = c1_y[c1_i148];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_k_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i149;
  int32_T c1_i150;
  int32_T c1_i151;
  real_T c1_b_inData[36];
  int32_T c1_i152;
  int32_T c1_i153;
  int32_T c1_i154;
  real_T c1_u[36];
  const mxArray *c1_y = NULL;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i149 = 0;
  for (c1_i150 = 0; c1_i150 < 6; c1_i150++) {
    for (c1_i151 = 0; c1_i151 < 6; c1_i151++) {
      c1_b_inData[c1_i151 + c1_i149] = (*(real_T (*)[36])c1_inData)[c1_i151 +
        c1_i149];
    }

    c1_i149 += 6;
  }

  c1_i152 = 0;
  for (c1_i153 = 0; c1_i153 < 6; c1_i153++) {
    for (c1_i154 = 0; c1_i154 < 6; c1_i154++) {
      c1_u[c1_i154 + c1_i152] = c1_b_inData[c1_i154 + c1_i152];
    }

    c1_i152 += 6;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 6, 6), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_t_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[36])
{
  real_T c1_dv24[36];
  int32_T c1_i155;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv24, 1, 0, 0U, 1, 0U, 2, 6, 6);
  for (c1_i155 = 0; c1_i155 < 36; c1_i155++) {
    c1_y[c1_i155] = c1_dv24[c1_i155];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_S;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[36];
  int32_T c1_i156;
  int32_T c1_i157;
  int32_T c1_i158;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_S = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_t_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_S), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_S);
  c1_i156 = 0;
  for (c1_i157 = 0; c1_i157 < 6; c1_i157++) {
    for (c1_i158 = 0; c1_i158 < 6; c1_i158++) {
      (*(real_T (*)[36])c1_outData)[c1_i158 + c1_i156] = c1_y[c1_i158 + c1_i156];
    }

    c1_i156 += 6;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_l_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i159;
  int32_T c1_i160;
  int32_T c1_i161;
  real_T c1_b_inData[114];
  int32_T c1_i162;
  int32_T c1_i163;
  int32_T c1_i164;
  real_T c1_u[114];
  const mxArray *c1_y = NULL;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i159 = 0;
  for (c1_i160 = 0; c1_i160 < 19; c1_i160++) {
    for (c1_i161 = 0; c1_i161 < 6; c1_i161++) {
      c1_b_inData[c1_i161 + c1_i159] = (*(real_T (*)[114])c1_inData)[c1_i161 +
        c1_i159];
    }

    c1_i159 += 6;
  }

  c1_i162 = 0;
  for (c1_i163 = 0; c1_i163 < 19; c1_i163++) {
    for (c1_i164 = 0; c1_i164 < 6; c1_i164++) {
      c1_u[c1_i164 + c1_i162] = c1_b_inData[c1_i164 + c1_i162];
    }

    c1_i162 += 6;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 6, 19), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_m_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i165;
  int32_T c1_i166;
  int32_T c1_i167;
  real_T c1_b_inData[114];
  int32_T c1_i168;
  int32_T c1_i169;
  int32_T c1_i170;
  real_T c1_u[114];
  const mxArray *c1_y = NULL;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i165 = 0;
  for (c1_i166 = 0; c1_i166 < 6; c1_i166++) {
    for (c1_i167 = 0; c1_i167 < 19; c1_i167++) {
      c1_b_inData[c1_i167 + c1_i165] = (*(real_T (*)[114])c1_inData)[c1_i167 +
        c1_i165];
    }

    c1_i165 += 19;
  }

  c1_i168 = 0;
  for (c1_i169 = 0; c1_i169 < 6; c1_i169++) {
    for (c1_i170 = 0; c1_i170 < 19; c1_i170++) {
      c1_u[c1_i170 + c1_i168] = c1_b_inData[c1_i170 + c1_i168];
    }

    c1_i168 += 19;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 19, 6), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_u_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[114])
{
  real_T c1_dv25[114];
  int32_T c1_i171;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv25, 1, 0, 0U, 1, 0U, 2, 19,
                6);
  for (c1_i171 = 0; c1_i171 < 114; c1_i171++) {
    c1_y[c1_i171] = c1_dv25[c1_i171];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_K;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[114];
  int32_T c1_i172;
  int32_T c1_i173;
  int32_T c1_i174;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_K = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_u_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_K), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_K);
  c1_i172 = 0;
  for (c1_i173 = 0; c1_i173 < 6; c1_i173++) {
    for (c1_i174 = 0; c1_i174 < 19; c1_i174++) {
      (*(real_T (*)[114])c1_outData)[c1_i174 + c1_i172] = c1_y[c1_i174 + c1_i172];
    }

    c1_i172 += 19;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_n_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i175;
  int32_T c1_i176;
  int32_T c1_i177;
  real_T c1_b_inData[361];
  int32_T c1_i178;
  int32_T c1_i179;
  int32_T c1_i180;
  real_T c1_u[361];
  const mxArray *c1_y = NULL;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i175 = 0;
  for (c1_i176 = 0; c1_i176 < 19; c1_i176++) {
    for (c1_i177 = 0; c1_i177 < 19; c1_i177++) {
      c1_b_inData[c1_i177 + c1_i175] = (*(real_T (*)[361])c1_inData)[c1_i177 +
        c1_i175];
    }

    c1_i175 += 19;
  }

  c1_i178 = 0;
  for (c1_i179 = 0; c1_i179 < 19; c1_i179++) {
    for (c1_i180 = 0; c1_i180 < 19; c1_i180++) {
      c1_u[c1_i180 + c1_i178] = c1_b_inData[c1_i180 + c1_i178];
    }

    c1_i178 += 19;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 19, 19), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_v_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[361])
{
  real_T c1_dv26[361];
  int32_T c1_i181;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv26, 1, 0, 0U, 1, 0U, 2, 19,
                19);
  for (c1_i181 = 0; c1_i181 < 361; c1_i181++) {
    c1_y[c1_i181] = c1_dv26[c1_i181];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_F;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[361];
  int32_T c1_i182;
  int32_T c1_i183;
  int32_T c1_i184;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_F = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_v_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_F), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_F);
  c1_i182 = 0;
  for (c1_i183 = 0; c1_i183 < 19; c1_i183++) {
    for (c1_i184 = 0; c1_i184 < 19; c1_i184++) {
      (*(real_T (*)[361])c1_outData)[c1_i184 + c1_i182] = c1_y[c1_i184 + c1_i182];
    }

    c1_i182 += 19;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray
  *sf_c1_aircraftControl_smallerStateEKF_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_createstruct("structure", 2, 195, 1),
                false);
  c1_info_helper(&c1_nameCaptureInfo);
  c1_b_info_helper(&c1_nameCaptureInfo);
  c1_c_info_helper(&c1_nameCaptureInfo);
  c1_d_info_helper(&c1_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(const mxArray **c1_info)
{
  const mxArray *c1_rhs0 = NULL;
  const mxArray *c1_lhs0 = NULL;
  const mxArray *c1_rhs1 = NULL;
  const mxArray *c1_lhs1 = NULL;
  const mxArray *c1_rhs2 = NULL;
  const mxArray *c1_lhs2 = NULL;
  const mxArray *c1_rhs3 = NULL;
  const mxArray *c1_lhs3 = NULL;
  const mxArray *c1_rhs4 = NULL;
  const mxArray *c1_lhs4 = NULL;
  const mxArray *c1_rhs5 = NULL;
  const mxArray *c1_lhs5 = NULL;
  const mxArray *c1_rhs6 = NULL;
  const mxArray *c1_lhs6 = NULL;
  const mxArray *c1_rhs7 = NULL;
  const mxArray *c1_lhs7 = NULL;
  const mxArray *c1_rhs8 = NULL;
  const mxArray *c1_lhs8 = NULL;
  const mxArray *c1_rhs9 = NULL;
  const mxArray *c1_lhs9 = NULL;
  const mxArray *c1_rhs10 = NULL;
  const mxArray *c1_lhs10 = NULL;
  const mxArray *c1_rhs11 = NULL;
  const mxArray *c1_lhs11 = NULL;
  const mxArray *c1_rhs12 = NULL;
  const mxArray *c1_lhs12 = NULL;
  const mxArray *c1_rhs13 = NULL;
  const mxArray *c1_lhs13 = NULL;
  const mxArray *c1_rhs14 = NULL;
  const mxArray *c1_lhs14 = NULL;
  const mxArray *c1_rhs15 = NULL;
  const mxArray *c1_lhs15 = NULL;
  const mxArray *c1_rhs16 = NULL;
  const mxArray *c1_lhs16 = NULL;
  const mxArray *c1_rhs17 = NULL;
  const mxArray *c1_lhs17 = NULL;
  const mxArray *c1_rhs18 = NULL;
  const mxArray *c1_lhs18 = NULL;
  const mxArray *c1_rhs19 = NULL;
  const mxArray *c1_lhs19 = NULL;
  const mxArray *c1_rhs20 = NULL;
  const mxArray *c1_lhs20 = NULL;
  const mxArray *c1_rhs21 = NULL;
  const mxArray *c1_lhs21 = NULL;
  const mxArray *c1_rhs22 = NULL;
  const mxArray *c1_lhs22 = NULL;
  const mxArray *c1_rhs23 = NULL;
  const mxArray *c1_lhs23 = NULL;
  const mxArray *c1_rhs24 = NULL;
  const mxArray *c1_lhs24 = NULL;
  const mxArray *c1_rhs25 = NULL;
  const mxArray *c1_lhs25 = NULL;
  const mxArray *c1_rhs26 = NULL;
  const mxArray *c1_lhs26 = NULL;
  const mxArray *c1_rhs27 = NULL;
  const mxArray *c1_lhs27 = NULL;
  const mxArray *c1_rhs28 = NULL;
  const mxArray *c1_lhs28 = NULL;
  const mxArray *c1_rhs29 = NULL;
  const mxArray *c1_lhs29 = NULL;
  const mxArray *c1_rhs30 = NULL;
  const mxArray *c1_lhs30 = NULL;
  const mxArray *c1_rhs31 = NULL;
  const mxArray *c1_lhs31 = NULL;
  const mxArray *c1_rhs32 = NULL;
  const mxArray *c1_lhs32 = NULL;
  const mxArray *c1_rhs33 = NULL;
  const mxArray *c1_lhs33 = NULL;
  const mxArray *c1_rhs34 = NULL;
  const mxArray *c1_lhs34 = NULL;
  const mxArray *c1_rhs35 = NULL;
  const mxArray *c1_lhs35 = NULL;
  const mxArray *c1_rhs36 = NULL;
  const mxArray *c1_lhs36 = NULL;
  const mxArray *c1_rhs37 = NULL;
  const mxArray *c1_lhs37 = NULL;
  const mxArray *c1_rhs38 = NULL;
  const mxArray *c1_lhs38 = NULL;
  const mxArray *c1_rhs39 = NULL;
  const mxArray *c1_lhs39 = NULL;
  const mxArray *c1_rhs40 = NULL;
  const mxArray *c1_lhs40 = NULL;
  const mxArray *c1_rhs41 = NULL;
  const mxArray *c1_lhs41 = NULL;
  const mxArray *c1_rhs42 = NULL;
  const mxArray *c1_lhs42 = NULL;
  const mxArray *c1_rhs43 = NULL;
  const mxArray *c1_lhs43 = NULL;
  const mxArray *c1_rhs44 = NULL;
  const mxArray *c1_lhs44 = NULL;
  const mxArray *c1_rhs45 = NULL;
  const mxArray *c1_lhs45 = NULL;
  const mxArray *c1_rhs46 = NULL;
  const mxArray *c1_lhs46 = NULL;
  const mxArray *c1_rhs47 = NULL;
  const mxArray *c1_lhs47 = NULL;
  const mxArray *c1_rhs48 = NULL;
  const mxArray *c1_lhs48 = NULL;
  const mxArray *c1_rhs49 = NULL;
  const mxArray *c1_lhs49 = NULL;
  const mxArray *c1_rhs50 = NULL;
  const mxArray *c1_lhs50 = NULL;
  const mxArray *c1_rhs51 = NULL;
  const mxArray *c1_lhs51 = NULL;
  const mxArray *c1_rhs52 = NULL;
  const mxArray *c1_lhs52 = NULL;
  const mxArray *c1_rhs53 = NULL;
  const mxArray *c1_lhs53 = NULL;
  const mxArray *c1_rhs54 = NULL;
  const mxArray *c1_lhs54 = NULL;
  const mxArray *c1_rhs55 = NULL;
  const mxArray *c1_lhs55 = NULL;
  const mxArray *c1_rhs56 = NULL;
  const mxArray *c1_lhs56 = NULL;
  const mxArray *c1_rhs57 = NULL;
  const mxArray *c1_lhs57 = NULL;
  const mxArray *c1_rhs58 = NULL;
  const mxArray *c1_lhs58 = NULL;
  const mxArray *c1_rhs59 = NULL;
  const mxArray *c1_lhs59 = NULL;
  const mxArray *c1_rhs60 = NULL;
  const mxArray *c1_lhs60 = NULL;
  const mxArray *c1_rhs61 = NULL;
  const mxArray *c1_lhs61 = NULL;
  const mxArray *c1_rhs62 = NULL;
  const mxArray *c1_lhs62 = NULL;
  const mxArray *c1_rhs63 = NULL;
  const mxArray *c1_lhs63 = NULL;
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("simulateEKF_smallerStateVec"),
                  "name", "name", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Rudaba/Documents/PHD TAKE 2/Simulations/AircraftModelling/simulateEKF_smallerStateVec.m"),
                  "resolved", "resolved", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1427506050U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c1_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Rudaba/Documents/PHD TAKE 2/Simulations/AircraftModelling/simulateEKF_smallerStateVec.m"),
                  "context", "context", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mpower"), "name", "name", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "resolved",
                  "resolved", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363677878U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c1_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363678556U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c1_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("ismatrix"), "name", "name", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ismatrix.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1331268858U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c1_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("power"), "name", "name", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "resolved",
                  "resolved", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363677880U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c1_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "context",
                  "context", 5);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 5);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363678556U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c1_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 6);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 6);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 6);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c1_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 7);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271920U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c1_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 8);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 8);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c1_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 9);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 9);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271920U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c1_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 10);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("floor"), "name", "name", 10);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 10);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363677854U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c1_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 11);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 11);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363678556U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c1_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 12);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 12);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286786326U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c1_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power"),
                  "context", "context", 13);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 13);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c1_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Rudaba/Documents/PHD TAKE 2/Simulations/AircraftModelling/simulateEKF_smallerStateVec.m"),
                  "context", "context", 14);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eye"), "name", "name", 14);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m"), "resolved",
                  "resolved", 14);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1381817898U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c1_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m"), "context",
                  "context", 15);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_assert_valid_size_arg"),
                  "name", "name", 15);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m"),
                  "resolved", "resolved", 15);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1368154230U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c1_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m"),
                  "context", "context", 16);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 16);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 16);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363678556U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c1_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral"),
                  "context", "context", 17);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("isinf"), "name", "name", 17);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m"), "resolved",
                  "resolved", 17);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363677856U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c1_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m"), "context",
                  "context", 18);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 18);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 18);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363678556U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c1_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isinbounds"),
                  "context", "context", 19);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_is_integer_class"), "name",
                  "name", 19);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_integer_class.m"),
                  "resolved", "resolved", 19);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286786382U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c1_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isinbounds"),
                  "context", "context", 20);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmax"), "name", "name", 20);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 20);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362225882U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c1_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "context",
                  "context", 21);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 21);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 21);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1381817900U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c1_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isinbounds"),
                  "context", "context", 22);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmin"), "name", "name", 22);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 22);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362225882U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c1_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "context",
                  "context", 23);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 23);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 23);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1381817900U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c1_rhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isinbounds"),
                  "context", "context", 24);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexIntRelop"),
                  "name", "name", 24);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m"),
                  "resolved", "resolved", 24);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1326692322U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c1_rhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!apply_float_relop"),
                  "context", "context", 25);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 25);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 25);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 25);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1381817900U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c1_rhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!float_class_contains_indexIntClass"),
                  "context", "context", 26);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 26);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 26);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1326691996U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c1_rhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!is_signed_indexIntClass"),
                  "context", "context", 27);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmin"), "name", "name", 27);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 27);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362225882U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c1_rhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m"),
                  "context", "context", 28);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 28);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 28);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 28);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323134578U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c1_rhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m"),
                  "context", "context", 29);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmax"), "name", "name", 29);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 29);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 29);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362225882U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c1_rhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m"), "context",
                  "context", 30);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 30);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 30);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 30);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c1_rhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs30), "lhs", "lhs",
                  30);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 31);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmax"), "name", "name", 31);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 31);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 31);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362225882U), "fileTimeLo",
                  "fileTimeLo", 31);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 31);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 31);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 31);
  sf_mex_assign(&c1_rhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs31), "rhs", "rhs",
                  31);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs31), "lhs", "lhs",
                  31);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Rudaba/Documents/PHD TAKE 2/Simulations/AircraftModelling/simulateEKF_smallerStateVec.m"),
                  "context", "context", 32);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 32);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 32);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 32);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1383841294U), "fileTimeLo",
                  "fileTimeLo", 32);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 32);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 32);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 32);
  sf_mex_assign(&c1_rhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs32), "rhs", "rhs",
                  32);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs32), "lhs", "lhs",
                  32);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 33);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 33);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 33);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 33);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363678556U), "fileTimeLo",
                  "fileTimeLo", 33);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 33);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 33);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 33);
  sf_mex_assign(&c1_rhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs33), "rhs", "rhs",
                  33);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs33), "lhs", "lhs",
                  33);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Rudaba/Documents/PHD TAKE 2/Simulations/AircraftModelling/simulateEKF_smallerStateVec.m"),
                  "context", "context", 34);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("power"), "name", "name", 34);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 34);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "resolved",
                  "resolved", 34);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363677880U), "fileTimeLo",
                  "fileTimeLo", 34);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 34);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 34);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 34);
  sf_mex_assign(&c1_rhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs34), "rhs", "rhs",
                  34);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs34), "lhs", "lhs",
                  34);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Rudaba/Documents/PHD TAKE 2/Simulations/AircraftModelling/simulateEKF_smallerStateVec.m"),
                  "context", "context", 35);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mrdivide"), "name", "name", 35);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 35);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 35);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1388424096U), "fileTimeLo",
                  "fileTimeLo", 35);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 35);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1369981086U), "mFileTimeLo",
                  "mFileTimeLo", 35);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 35);
  sf_mex_assign(&c1_rhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs35), "rhs", "rhs",
                  35);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs35), "lhs", "lhs",
                  35);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 36);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 36);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 36);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 36);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363678556U), "fileTimeLo",
                  "fileTimeLo", 36);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 36);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 36);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 36);
  sf_mex_assign(&c1_rhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs36), "rhs", "rhs",
                  36);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs36), "lhs", "lhs",
                  36);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 37);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("rdivide"), "name", "name", 37);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 37);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 37);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363677880U), "fileTimeLo",
                  "fileTimeLo", 37);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 37);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 37);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 37);
  sf_mex_assign(&c1_rhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs37), "rhs", "rhs",
                  37);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs37), "lhs", "lhs",
                  37);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 38);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 38);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 38);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 38);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363678556U), "fileTimeLo",
                  "fileTimeLo", 38);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 38);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 38);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 38);
  sf_mex_assign(&c1_rhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs38), "rhs", "rhs",
                  38);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs38), "lhs", "lhs",
                  38);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 39);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 39);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 39);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 39);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286786396U), "fileTimeLo",
                  "fileTimeLo", 39);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 39);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 39);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 39);
  sf_mex_assign(&c1_rhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs39), "rhs", "rhs",
                  39);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs39), "lhs", "lhs",
                  39);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 40);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_div"), "name", "name", 40);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 40);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 40);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 40);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 40);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 40);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 40);
  sf_mex_assign(&c1_rhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs40), "rhs", "rhs",
                  40);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs40), "lhs", "lhs",
                  40);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 41);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 41);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 41);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 41);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271920U), "fileTimeLo",
                  "fileTimeLo", 41);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 41);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 41);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 41);
  sf_mex_assign(&c1_rhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs41), "rhs", "rhs",
                  41);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs41), "lhs", "lhs",
                  41);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 42);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 42);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 42);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 42);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323134578U), "fileTimeLo",
                  "fileTimeLo", 42);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 42);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 42);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 42);
  sf_mex_assign(&c1_rhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs42), "rhs", "rhs",
                  42);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs42), "lhs", "lhs",
                  42);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 43);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 43);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 43);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 43);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 43);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 43);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 43);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 43);
  sf_mex_assign(&c1_rhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs43), "rhs", "rhs",
                  43);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs43), "lhs", "lhs",
                  43);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 44);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_xgemm"), "name", "name",
                  44);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 44);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"),
                  "resolved", "resolved", 44);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951890U), "fileTimeLo",
                  "fileTimeLo", 44);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 44);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 44);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 44);
  sf_mex_assign(&c1_rhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs44), "rhs", "rhs",
                  44);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs44), "lhs", "lhs",
                  44);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 45);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 45);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 45);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 45);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 45);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 45);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 45);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 45);
  sf_mex_assign(&c1_rhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs45), "rhs", "rhs",
                  45);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs45), "lhs", "lhs",
                  45);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 46);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.xgemm"),
                  "name", "name", 46);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 46);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "resolved", "resolved", 46);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 46);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 46);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 46);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 46);
  sf_mex_assign(&c1_rhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs46), "rhs", "rhs",
                  46);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs46), "lhs", "lhs",
                  46);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 47);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 47);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 47);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 47);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 47);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 47);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 47);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 47);
  sf_mex_assign(&c1_rhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs47), "rhs", "rhs",
                  47);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs47), "lhs", "lhs",
                  47);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!below_threshold"),
                  "context", "context", 48);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 48);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 48);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 48);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 48);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 48);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 48);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 48);
  sf_mex_assign(&c1_rhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs48), "rhs", "rhs",
                  48);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs48), "lhs", "lhs",
                  48);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "context", "context", 49);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 49);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 49);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 49);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1381817900U), "fileTimeLo",
                  "fileTimeLo", 49);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 49);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 49);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 49);
  sf_mex_assign(&c1_rhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs49), "rhs", "rhs",
                  49);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs49), "lhs", "lhs",
                  49);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 50);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 50);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 50);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 50);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271920U), "fileTimeLo",
                  "fileTimeLo", 50);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 50);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 50);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 50);
  sf_mex_assign(&c1_rhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs50), "rhs", "rhs",
                  50);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs50), "lhs", "lhs",
                  50);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 51);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.refblas.xgemm"),
                  "name", "name", 51);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 51);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "resolved", "resolved", 51);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 51);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 51);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 51);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 51);
  sf_mex_assign(&c1_rhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs51), "rhs", "rhs",
                  51);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs51), "lhs", "lhs",
                  51);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 52);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.int"),
                  "name", "name", 52);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 52);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/int.p"),
                  "resolved", "resolved", 52);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 52);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 52);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 52);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 52);
  sf_mex_assign(&c1_rhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs52), "rhs", "rhs",
                  52);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs52), "lhs", "lhs",
                  52);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!ceval_xgemm"),
                  "context", "context", 53);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.size_ptr"),
                  "name", "name", 53);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 53);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/size_ptr.p"),
                  "resolved", "resolved", 53);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 53);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 53);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 53);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 53);
  sf_mex_assign(&c1_rhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs53), "rhs", "rhs",
                  53);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs53), "lhs", "lhs",
                  53);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!ceval_xgemm"),
                  "context", "context", 54);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.c_cast"),
                  "name", "name", 54);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("int32"), "dominantType",
                  "dominantType", 54);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/c_cast.p"),
                  "resolved", "resolved", 54);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271920U), "fileTimeLo",
                  "fileTimeLo", 54);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 54);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 54);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 54);
  sf_mex_assign(&c1_rhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs54), "rhs", "rhs",
                  54);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs54), "lhs", "lhs",
                  54);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Rudaba/Documents/PHD TAKE 2/Simulations/AircraftModelling/simulateEKF_smallerStateVec.m"),
                  "context", "context", 55);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("inv"), "name", "name", 55);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 55);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m"), "resolved",
                  "resolved", 55);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1305289200U), "fileTimeLo",
                  "fileTimeLo", 55);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 55);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 55);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 55);
  sf_mex_assign(&c1_rhs55, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs55, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs55), "rhs", "rhs",
                  55);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs55), "lhs", "lhs",
                  55);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN"), "context",
                  "context", 56);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 56);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 56);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 56);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323134578U), "fileTimeLo",
                  "fileTimeLo", 56);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 56);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 56);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 56);
  sf_mex_assign(&c1_rhs56, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs56, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs56), "rhs", "rhs",
                  56);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs56), "lhs", "lhs",
                  56);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN"), "context",
                  "context", 57);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_xgetrf"), "name", "name",
                  57);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 57);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m"),
                  "resolved", "resolved", 57);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286786406U), "fileTimeLo",
                  "fileTimeLo", 57);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 57);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 57);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 57);
  sf_mex_assign(&c1_rhs57, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs57, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs57), "rhs", "rhs",
                  57);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs57), "lhs", "lhs",
                  57);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m"),
                  "context", "context", 58);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_lapack_xgetrf"), "name",
                  "name", 58);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 58);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m"),
                  "resolved", "resolved", 58);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286786410U), "fileTimeLo",
                  "fileTimeLo", 58);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 58);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 58);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 58);
  sf_mex_assign(&c1_rhs58, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs58, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs58), "rhs", "rhs",
                  58);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs58), "lhs", "lhs",
                  58);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m"),
                  "context", "context", 59);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_matlab_zgetrf"), "name",
                  "name", 59);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 59);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "resolved", "resolved", 59);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1302660194U), "fileTimeLo",
                  "fileTimeLo", 59);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 59);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 59);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 59);
  sf_mex_assign(&c1_rhs59, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs59, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs59), "rhs", "rhs",
                  59);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs59), "lhs", "lhs",
                  59);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 60);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("realmin"), "name", "name", 60);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 60);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m"), "resolved",
                  "resolved", 60);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1307622442U), "fileTimeLo",
                  "fileTimeLo", 60);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 60);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 60);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 60);
  sf_mex_assign(&c1_rhs60, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs60, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs60), "rhs", "rhs",
                  60);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs60), "lhs", "lhs",
                  60);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m"), "context",
                  "context", 61);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_realmin"), "name", "name",
                  61);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 61);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m"), "resolved",
                  "resolved", 61);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1307622444U), "fileTimeLo",
                  "fileTimeLo", 61);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 61);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 61);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 61);
  sf_mex_assign(&c1_rhs61, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs61, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs61), "rhs", "rhs",
                  61);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs61), "lhs", "lhs",
                  61);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m"), "context",
                  "context", 62);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 62);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 62);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 62);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1326691996U), "fileTimeLo",
                  "fileTimeLo", 62);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 62);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 62);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 62);
  sf_mex_assign(&c1_rhs62, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs62, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs62), "rhs", "rhs",
                  62);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs62), "lhs", "lhs",
                  62);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 63);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eps"), "name", "name", 63);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 63);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "resolved",
                  "resolved", 63);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1326691996U), "fileTimeLo",
                  "fileTimeLo", 63);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 63);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 63);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 63);
  sf_mex_assign(&c1_rhs63, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs63, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs63), "rhs", "rhs",
                  63);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs63), "lhs", "lhs",
                  63);
  sf_mex_destroy(&c1_rhs0);
  sf_mex_destroy(&c1_lhs0);
  sf_mex_destroy(&c1_rhs1);
  sf_mex_destroy(&c1_lhs1);
  sf_mex_destroy(&c1_rhs2);
  sf_mex_destroy(&c1_lhs2);
  sf_mex_destroy(&c1_rhs3);
  sf_mex_destroy(&c1_lhs3);
  sf_mex_destroy(&c1_rhs4);
  sf_mex_destroy(&c1_lhs4);
  sf_mex_destroy(&c1_rhs5);
  sf_mex_destroy(&c1_lhs5);
  sf_mex_destroy(&c1_rhs6);
  sf_mex_destroy(&c1_lhs6);
  sf_mex_destroy(&c1_rhs7);
  sf_mex_destroy(&c1_lhs7);
  sf_mex_destroy(&c1_rhs8);
  sf_mex_destroy(&c1_lhs8);
  sf_mex_destroy(&c1_rhs9);
  sf_mex_destroy(&c1_lhs9);
  sf_mex_destroy(&c1_rhs10);
  sf_mex_destroy(&c1_lhs10);
  sf_mex_destroy(&c1_rhs11);
  sf_mex_destroy(&c1_lhs11);
  sf_mex_destroy(&c1_rhs12);
  sf_mex_destroy(&c1_lhs12);
  sf_mex_destroy(&c1_rhs13);
  sf_mex_destroy(&c1_lhs13);
  sf_mex_destroy(&c1_rhs14);
  sf_mex_destroy(&c1_lhs14);
  sf_mex_destroy(&c1_rhs15);
  sf_mex_destroy(&c1_lhs15);
  sf_mex_destroy(&c1_rhs16);
  sf_mex_destroy(&c1_lhs16);
  sf_mex_destroy(&c1_rhs17);
  sf_mex_destroy(&c1_lhs17);
  sf_mex_destroy(&c1_rhs18);
  sf_mex_destroy(&c1_lhs18);
  sf_mex_destroy(&c1_rhs19);
  sf_mex_destroy(&c1_lhs19);
  sf_mex_destroy(&c1_rhs20);
  sf_mex_destroy(&c1_lhs20);
  sf_mex_destroy(&c1_rhs21);
  sf_mex_destroy(&c1_lhs21);
  sf_mex_destroy(&c1_rhs22);
  sf_mex_destroy(&c1_lhs22);
  sf_mex_destroy(&c1_rhs23);
  sf_mex_destroy(&c1_lhs23);
  sf_mex_destroy(&c1_rhs24);
  sf_mex_destroy(&c1_lhs24);
  sf_mex_destroy(&c1_rhs25);
  sf_mex_destroy(&c1_lhs25);
  sf_mex_destroy(&c1_rhs26);
  sf_mex_destroy(&c1_lhs26);
  sf_mex_destroy(&c1_rhs27);
  sf_mex_destroy(&c1_lhs27);
  sf_mex_destroy(&c1_rhs28);
  sf_mex_destroy(&c1_lhs28);
  sf_mex_destroy(&c1_rhs29);
  sf_mex_destroy(&c1_lhs29);
  sf_mex_destroy(&c1_rhs30);
  sf_mex_destroy(&c1_lhs30);
  sf_mex_destroy(&c1_rhs31);
  sf_mex_destroy(&c1_lhs31);
  sf_mex_destroy(&c1_rhs32);
  sf_mex_destroy(&c1_lhs32);
  sf_mex_destroy(&c1_rhs33);
  sf_mex_destroy(&c1_lhs33);
  sf_mex_destroy(&c1_rhs34);
  sf_mex_destroy(&c1_lhs34);
  sf_mex_destroy(&c1_rhs35);
  sf_mex_destroy(&c1_lhs35);
  sf_mex_destroy(&c1_rhs36);
  sf_mex_destroy(&c1_lhs36);
  sf_mex_destroy(&c1_rhs37);
  sf_mex_destroy(&c1_lhs37);
  sf_mex_destroy(&c1_rhs38);
  sf_mex_destroy(&c1_lhs38);
  sf_mex_destroy(&c1_rhs39);
  sf_mex_destroy(&c1_lhs39);
  sf_mex_destroy(&c1_rhs40);
  sf_mex_destroy(&c1_lhs40);
  sf_mex_destroy(&c1_rhs41);
  sf_mex_destroy(&c1_lhs41);
  sf_mex_destroy(&c1_rhs42);
  sf_mex_destroy(&c1_lhs42);
  sf_mex_destroy(&c1_rhs43);
  sf_mex_destroy(&c1_lhs43);
  sf_mex_destroy(&c1_rhs44);
  sf_mex_destroy(&c1_lhs44);
  sf_mex_destroy(&c1_rhs45);
  sf_mex_destroy(&c1_lhs45);
  sf_mex_destroy(&c1_rhs46);
  sf_mex_destroy(&c1_lhs46);
  sf_mex_destroy(&c1_rhs47);
  sf_mex_destroy(&c1_lhs47);
  sf_mex_destroy(&c1_rhs48);
  sf_mex_destroy(&c1_lhs48);
  sf_mex_destroy(&c1_rhs49);
  sf_mex_destroy(&c1_lhs49);
  sf_mex_destroy(&c1_rhs50);
  sf_mex_destroy(&c1_lhs50);
  sf_mex_destroy(&c1_rhs51);
  sf_mex_destroy(&c1_lhs51);
  sf_mex_destroy(&c1_rhs52);
  sf_mex_destroy(&c1_lhs52);
  sf_mex_destroy(&c1_rhs53);
  sf_mex_destroy(&c1_lhs53);
  sf_mex_destroy(&c1_rhs54);
  sf_mex_destroy(&c1_lhs54);
  sf_mex_destroy(&c1_rhs55);
  sf_mex_destroy(&c1_lhs55);
  sf_mex_destroy(&c1_rhs56);
  sf_mex_destroy(&c1_lhs56);
  sf_mex_destroy(&c1_rhs57);
  sf_mex_destroy(&c1_lhs57);
  sf_mex_destroy(&c1_rhs58);
  sf_mex_destroy(&c1_lhs58);
  sf_mex_destroy(&c1_rhs59);
  sf_mex_destroy(&c1_lhs59);
  sf_mex_destroy(&c1_rhs60);
  sf_mex_destroy(&c1_lhs60);
  sf_mex_destroy(&c1_rhs61);
  sf_mex_destroy(&c1_lhs61);
  sf_mex_destroy(&c1_rhs62);
  sf_mex_destroy(&c1_lhs62);
  sf_mex_destroy(&c1_rhs63);
  sf_mex_destroy(&c1_lhs63);
}

static const mxArray *c1_emlrt_marshallOut(const char * c1_u)
{
  const mxArray *c1_y = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c1_u)), false);
  return c1_y;
}

static const mxArray *c1_b_emlrt_marshallOut(const uint32_T c1_u)
{
  const mxArray *c1_y = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 7, 0U, 0U, 0U, 0), false);
  return c1_y;
}

static void c1_b_info_helper(const mxArray **c1_info)
{
  const mxArray *c1_rhs64 = NULL;
  const mxArray *c1_lhs64 = NULL;
  const mxArray *c1_rhs65 = NULL;
  const mxArray *c1_lhs65 = NULL;
  const mxArray *c1_rhs66 = NULL;
  const mxArray *c1_lhs66 = NULL;
  const mxArray *c1_rhs67 = NULL;
  const mxArray *c1_lhs67 = NULL;
  const mxArray *c1_rhs68 = NULL;
  const mxArray *c1_lhs68 = NULL;
  const mxArray *c1_rhs69 = NULL;
  const mxArray *c1_lhs69 = NULL;
  const mxArray *c1_rhs70 = NULL;
  const mxArray *c1_lhs70 = NULL;
  const mxArray *c1_rhs71 = NULL;
  const mxArray *c1_lhs71 = NULL;
  const mxArray *c1_rhs72 = NULL;
  const mxArray *c1_lhs72 = NULL;
  const mxArray *c1_rhs73 = NULL;
  const mxArray *c1_lhs73 = NULL;
  const mxArray *c1_rhs74 = NULL;
  const mxArray *c1_lhs74 = NULL;
  const mxArray *c1_rhs75 = NULL;
  const mxArray *c1_lhs75 = NULL;
  const mxArray *c1_rhs76 = NULL;
  const mxArray *c1_lhs76 = NULL;
  const mxArray *c1_rhs77 = NULL;
  const mxArray *c1_lhs77 = NULL;
  const mxArray *c1_rhs78 = NULL;
  const mxArray *c1_lhs78 = NULL;
  const mxArray *c1_rhs79 = NULL;
  const mxArray *c1_lhs79 = NULL;
  const mxArray *c1_rhs80 = NULL;
  const mxArray *c1_lhs80 = NULL;
  const mxArray *c1_rhs81 = NULL;
  const mxArray *c1_lhs81 = NULL;
  const mxArray *c1_rhs82 = NULL;
  const mxArray *c1_lhs82 = NULL;
  const mxArray *c1_rhs83 = NULL;
  const mxArray *c1_lhs83 = NULL;
  const mxArray *c1_rhs84 = NULL;
  const mxArray *c1_lhs84 = NULL;
  const mxArray *c1_rhs85 = NULL;
  const mxArray *c1_lhs85 = NULL;
  const mxArray *c1_rhs86 = NULL;
  const mxArray *c1_lhs86 = NULL;
  const mxArray *c1_rhs87 = NULL;
  const mxArray *c1_lhs87 = NULL;
  const mxArray *c1_rhs88 = NULL;
  const mxArray *c1_lhs88 = NULL;
  const mxArray *c1_rhs89 = NULL;
  const mxArray *c1_lhs89 = NULL;
  const mxArray *c1_rhs90 = NULL;
  const mxArray *c1_lhs90 = NULL;
  const mxArray *c1_rhs91 = NULL;
  const mxArray *c1_lhs91 = NULL;
  const mxArray *c1_rhs92 = NULL;
  const mxArray *c1_lhs92 = NULL;
  const mxArray *c1_rhs93 = NULL;
  const mxArray *c1_lhs93 = NULL;
  const mxArray *c1_rhs94 = NULL;
  const mxArray *c1_lhs94 = NULL;
  const mxArray *c1_rhs95 = NULL;
  const mxArray *c1_lhs95 = NULL;
  const mxArray *c1_rhs96 = NULL;
  const mxArray *c1_lhs96 = NULL;
  const mxArray *c1_rhs97 = NULL;
  const mxArray *c1_lhs97 = NULL;
  const mxArray *c1_rhs98 = NULL;
  const mxArray *c1_lhs98 = NULL;
  const mxArray *c1_rhs99 = NULL;
  const mxArray *c1_lhs99 = NULL;
  const mxArray *c1_rhs100 = NULL;
  const mxArray *c1_lhs100 = NULL;
  const mxArray *c1_rhs101 = NULL;
  const mxArray *c1_lhs101 = NULL;
  const mxArray *c1_rhs102 = NULL;
  const mxArray *c1_lhs102 = NULL;
  const mxArray *c1_rhs103 = NULL;
  const mxArray *c1_lhs103 = NULL;
  const mxArray *c1_rhs104 = NULL;
  const mxArray *c1_lhs104 = NULL;
  const mxArray *c1_rhs105 = NULL;
  const mxArray *c1_lhs105 = NULL;
  const mxArray *c1_rhs106 = NULL;
  const mxArray *c1_lhs106 = NULL;
  const mxArray *c1_rhs107 = NULL;
  const mxArray *c1_lhs107 = NULL;
  const mxArray *c1_rhs108 = NULL;
  const mxArray *c1_lhs108 = NULL;
  const mxArray *c1_rhs109 = NULL;
  const mxArray *c1_lhs109 = NULL;
  const mxArray *c1_rhs110 = NULL;
  const mxArray *c1_lhs110 = NULL;
  const mxArray *c1_rhs111 = NULL;
  const mxArray *c1_lhs111 = NULL;
  const mxArray *c1_rhs112 = NULL;
  const mxArray *c1_lhs112 = NULL;
  const mxArray *c1_rhs113 = NULL;
  const mxArray *c1_lhs113 = NULL;
  const mxArray *c1_rhs114 = NULL;
  const mxArray *c1_lhs114 = NULL;
  const mxArray *c1_rhs115 = NULL;
  const mxArray *c1_lhs115 = NULL;
  const mxArray *c1_rhs116 = NULL;
  const mxArray *c1_lhs116 = NULL;
  const mxArray *c1_rhs117 = NULL;
  const mxArray *c1_lhs117 = NULL;
  const mxArray *c1_rhs118 = NULL;
  const mxArray *c1_lhs118 = NULL;
  const mxArray *c1_rhs119 = NULL;
  const mxArray *c1_lhs119 = NULL;
  const mxArray *c1_rhs120 = NULL;
  const mxArray *c1_lhs120 = NULL;
  const mxArray *c1_rhs121 = NULL;
  const mxArray *c1_lhs121 = NULL;
  const mxArray *c1_rhs122 = NULL;
  const mxArray *c1_lhs122 = NULL;
  const mxArray *c1_rhs123 = NULL;
  const mxArray *c1_lhs123 = NULL;
  const mxArray *c1_rhs124 = NULL;
  const mxArray *c1_lhs124 = NULL;
  const mxArray *c1_rhs125 = NULL;
  const mxArray *c1_lhs125 = NULL;
  const mxArray *c1_rhs126 = NULL;
  const mxArray *c1_lhs126 = NULL;
  const mxArray *c1_rhs127 = NULL;
  const mxArray *c1_lhs127 = NULL;
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 64);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_is_float_class"), "name",
                  "name", 64);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 64);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m"),
                  "resolved", "resolved", 64);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286786382U), "fileTimeLo",
                  "fileTimeLo", 64);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 64);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 64);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 64);
  sf_mex_assign(&c1_rhs64, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs64, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs64), "rhs", "rhs",
                  64);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs64), "lhs", "lhs",
                  64);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 65);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_eps"), "name", "name", 65);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 65);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m"), "resolved",
                  "resolved", 65);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1326691996U), "fileTimeLo",
                  "fileTimeLo", 65);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 65);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 65);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 65);
  sf_mex_assign(&c1_rhs65, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs65, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs65), "rhs", "rhs",
                  65);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs65), "lhs", "lhs",
                  65);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m"), "context",
                  "context", 66);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 66);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 66);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 66);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1326691996U), "fileTimeLo",
                  "fileTimeLo", 66);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 66);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 66);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 66);
  sf_mex_assign(&c1_rhs66, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs66, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs66), "rhs", "rhs",
                  66);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs66), "lhs", "lhs",
                  66);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 67);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("min"), "name", "name", 67);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 67);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 67);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1311226518U), "fileTimeLo",
                  "fileTimeLo", 67);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 67);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 67);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 67);
  sf_mex_assign(&c1_rhs67, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs67, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs67), "rhs", "rhs",
                  67);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs67), "lhs", "lhs",
                  67);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "context",
                  "context", 68);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_min_or_max"), "name",
                  "name", 68);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 68);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m"),
                  "resolved", "resolved", 68);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1378267184U), "fileTimeLo",
                  "fileTimeLo", 68);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 68);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 68);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 68);
  sf_mex_assign(&c1_rhs68, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs68, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs68), "rhs", "rhs",
                  68);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs68), "lhs", "lhs",
                  68);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 69);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 69);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 69);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 69);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 69);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 69);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 69);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 69);
  sf_mex_assign(&c1_rhs69, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs69, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs69), "rhs", "rhs",
                  69);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs69), "lhs", "lhs",
                  69);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 70);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 70);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 70);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 70);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271920U), "fileTimeLo",
                  "fileTimeLo", 70);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 70);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 70);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 70);
  sf_mex_assign(&c1_rhs70, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs70, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs70), "rhs", "rhs",
                  70);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs70), "lhs", "lhs",
                  70);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 71);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 71);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 71);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 71);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 71);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 71);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 71);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 71);
  sf_mex_assign(&c1_rhs71, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs71, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs71), "rhs", "rhs",
                  71);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs71), "lhs", "lhs",
                  71);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 72);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 72);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 72);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 72);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271920U), "fileTimeLo",
                  "fileTimeLo", 72);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 72);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 72);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 72);
  sf_mex_assign(&c1_rhs72, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs72, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs72), "rhs", "rhs",
                  72);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs72), "lhs", "lhs",
                  72);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 73);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 73);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 73);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 73);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323134578U), "fileTimeLo",
                  "fileTimeLo", 73);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 73);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 73);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 73);
  sf_mex_assign(&c1_rhs73, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs73, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs73), "rhs", "rhs",
                  73);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs73), "lhs", "lhs",
                  73);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 74);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 74);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 74);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 74);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 74);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 74);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 74);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 74);
  sf_mex_assign(&c1_rhs74, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs74, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs74), "rhs", "rhs",
                  74);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs74), "lhs", "lhs",
                  74);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 75);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 75);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 75);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 75);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363678556U), "fileTimeLo",
                  "fileTimeLo", 75);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 75);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 75);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 75);
  sf_mex_assign(&c1_rhs75, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs75, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs75), "rhs", "rhs",
                  75);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs75), "lhs", "lhs",
                  75);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 76);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("colon"), "name", "name", 76);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 76);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 76);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1378267188U), "fileTimeLo",
                  "fileTimeLo", 76);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 76);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 76);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 76);
  sf_mex_assign(&c1_rhs76, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs76, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs76), "rhs", "rhs",
                  76);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs76), "lhs", "lhs",
                  76);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 77);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("colon"), "name", "name", 77);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 77);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 77);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1378267188U), "fileTimeLo",
                  "fileTimeLo", 77);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 77);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 77);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 77);
  sf_mex_assign(&c1_rhs77, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs77, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs77), "rhs", "rhs",
                  77);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs77), "lhs", "lhs",
                  77);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 78);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 78);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 78);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 78);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363678556U), "fileTimeLo",
                  "fileTimeLo", 78);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 78);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 78);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 78);
  sf_mex_assign(&c1_rhs78, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs78, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs78), "rhs", "rhs",
                  78);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs78), "lhs", "lhs",
                  78);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 79);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 79);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 79);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 79);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363678556U), "fileTimeLo",
                  "fileTimeLo", 79);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 79);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 79);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 79);
  sf_mex_assign(&c1_rhs79, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs79, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs79), "rhs", "rhs",
                  79);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs79), "lhs", "lhs",
                  79);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 80);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("floor"), "name", "name", 80);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 80);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 80);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363677854U), "fileTimeLo",
                  "fileTimeLo", 80);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 80);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 80);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 80);
  sf_mex_assign(&c1_rhs80, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs80, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs80), "rhs", "rhs",
                  80);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs80), "lhs", "lhs",
                  80);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange"),
                  "context", "context", 81);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmin"), "name", "name", 81);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 81);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 81);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362225882U), "fileTimeLo",
                  "fileTimeLo", 81);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 81);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 81);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 81);
  sf_mex_assign(&c1_rhs81, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs81, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs81), "rhs", "rhs",
                  81);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs81), "lhs", "lhs",
                  81);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange"),
                  "context", "context", 82);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmax"), "name", "name", 82);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 82);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 82);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362225882U), "fileTimeLo",
                  "fileTimeLo", 82);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 82);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 82);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 82);
  sf_mex_assign(&c1_rhs82, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs82, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs82), "rhs", "rhs",
                  82);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs82), "lhs", "lhs",
                  82);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 83);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmin"), "name", "name", 83);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 83);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 83);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362225882U), "fileTimeLo",
                  "fileTimeLo", 83);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 83);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 83);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 83);
  sf_mex_assign(&c1_rhs83, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs83, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs83), "rhs", "rhs",
                  83);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs83), "lhs", "lhs",
                  83);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 84);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmax"), "name", "name", 84);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 84);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 84);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362225882U), "fileTimeLo",
                  "fileTimeLo", 84);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 84);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 84);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 84);
  sf_mex_assign(&c1_rhs84, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs84, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs84), "rhs", "rhs",
                  84);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs84), "lhs", "lhs",
                  84);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 85);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_isa_uint"), "name", "name",
                  85);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 85);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "resolved",
                  "resolved", 85);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 85);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 85);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 85);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 85);
  sf_mex_assign(&c1_rhs85, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs85, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs85), "rhs", "rhs",
                  85);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs85), "lhs", "lhs",
                  85);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "context",
                  "context", 86);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.isaUint"),
                  "name", "name", 86);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 86);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/isaUint.p"),
                  "resolved", "resolved", 86);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271920U), "fileTimeLo",
                  "fileTimeLo", 86);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 86);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 86);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 86);
  sf_mex_assign(&c1_rhs86, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs86, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs86), "rhs", "rhs",
                  86);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs86), "lhs", "lhs",
                  86);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 87);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_unsigned_class"), "name",
                  "name", 87);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 87);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m"),
                  "resolved", "resolved", 87);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 87);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 87);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 87);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 87);
  sf_mex_assign(&c1_rhs87, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs87, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs87), "rhs", "rhs",
                  87);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs87), "lhs", "lhs",
                  87);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m"),
                  "context", "context", 88);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.unsignedClass"),
                  "name", "name", 88);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 88);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/unsignedClass.p"),
                  "resolved", "resolved", 88);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 88);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 88);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 88);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 88);
  sf_mex_assign(&c1_rhs88, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs88, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs88), "rhs", "rhs",
                  88);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs88), "lhs", "lhs",
                  88);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/unsignedClass.p"),
                  "context", "context", 89);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 89);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 89);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 89);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1381817900U), "fileTimeLo",
                  "fileTimeLo", 89);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 89);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 89);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 89);
  sf_mex_assign(&c1_rhs89, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs89, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs89), "rhs", "rhs",
                  89);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs89), "lhs", "lhs",
                  89);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/unsignedClass.p"),
                  "context", "context", 90);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 90);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 90);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 90);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323134578U), "fileTimeLo",
                  "fileTimeLo", 90);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 90);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 90);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 90);
  sf_mex_assign(&c1_rhs90, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs90, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs90), "rhs", "rhs",
                  90);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs90), "lhs", "lhs",
                  90);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 91);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 91);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 91);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 91);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323134578U), "fileTimeLo",
                  "fileTimeLo", 91);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 91);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 91);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 91);
  sf_mex_assign(&c1_rhs91, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs91, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs91), "rhs", "rhs",
                  91);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs91), "lhs", "lhs",
                  91);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 92);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmax"), "name", "name", 92);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 92);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 92);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362225882U), "fileTimeLo",
                  "fileTimeLo", 92);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 92);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 92);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 92);
  sf_mex_assign(&c1_rhs92, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs92, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs92), "rhs", "rhs",
                  92);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs92), "lhs", "lhs",
                  92);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 93);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_isa_uint"), "name", "name",
                  93);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 93);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "resolved",
                  "resolved", 93);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 93);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 93);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 93);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 93);
  sf_mex_assign(&c1_rhs93, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs93, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs93), "rhs", "rhs",
                  93);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs93), "lhs", "lhs",
                  93);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 94);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 94);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 94);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 94);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372553616U), "fileTimeLo",
                  "fileTimeLo", 94);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 94);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 94);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 94);
  sf_mex_assign(&c1_rhs94, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs94, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs94), "rhs", "rhs",
                  94);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs94), "lhs", "lhs",
                  94);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"), "context",
                  "context", 95);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 95);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 95);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 95);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372554360U), "fileTimeLo",
                  "fileTimeLo", 95);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 95);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 95);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 95);
  sf_mex_assign(&c1_rhs95, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs95, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs95), "rhs", "rhs",
                  95);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs95), "lhs", "lhs",
                  95);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_signed_integer_colon"),
                  "context", "context", 96);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 96);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 96);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 96);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 96);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 96);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 96);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 96);
  sf_mex_assign(&c1_rhs96, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs96, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs96), "rhs", "rhs",
                  96);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs96), "lhs", "lhs",
                  96);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 97);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 97);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 97);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 97);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323134578U), "fileTimeLo",
                  "fileTimeLo", 97);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 97);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 97);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 97);
  sf_mex_assign(&c1_rhs97, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs97, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs97), "rhs", "rhs",
                  97);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs97), "lhs", "lhs",
                  97);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 98);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 98);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 98);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 98);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372553616U), "fileTimeLo",
                  "fileTimeLo", 98);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 98);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 98);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 98);
  sf_mex_assign(&c1_rhs98, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs98, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs98), "rhs", "rhs",
                  98);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs98), "lhs", "lhs",
                  98);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 99);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 99);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 99);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 99);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 99);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 99);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 99);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 99);
  sf_mex_assign(&c1_rhs99, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs99, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs99), "rhs", "rhs",
                  99);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs99), "lhs", "lhs",
                  99);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 100);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 100);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 100);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 100);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372553616U), "fileTimeLo",
                  "fileTimeLo", 100);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 100);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 100);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 100);
  sf_mex_assign(&c1_rhs100, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs100, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs100), "rhs", "rhs",
                  100);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs100), "lhs", "lhs",
                  100);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "context", "context", 101);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 101);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 101);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 101);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372554360U), "fileTimeLo",
                  "fileTimeLo", 101);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 101);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 101);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 101);
  sf_mex_assign(&c1_rhs101, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs101, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs101), "rhs", "rhs",
                  101);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs101), "lhs", "lhs",
                  101);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 102);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 102);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 102);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 102);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372553616U), "fileTimeLo",
                  "fileTimeLo", 102);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 102);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 102);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 102);
  sf_mex_assign(&c1_rhs102, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs102, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs102), "rhs", "rhs",
                  102);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs102), "lhs", "lhs",
                  102);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "context", "context", 103);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 103);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 103);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 103);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372554360U), "fileTimeLo",
                  "fileTimeLo", 103);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 103);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 103);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 103);
  sf_mex_assign(&c1_rhs103, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs103, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs103), "rhs", "rhs",
                  103);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs103), "lhs", "lhs",
                  103);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 104);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_times"), "name",
                  "name", 104);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 104);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "resolved", "resolved", 104);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372553616U), "fileTimeLo",
                  "fileTimeLo", 104);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 104);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 104);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 104);
  sf_mex_assign(&c1_rhs104, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs104, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs104), "rhs", "rhs",
                  104);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs104), "lhs", "lhs",
                  104);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "context", "context", 105);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexTimes"),
                  "name", "name", 105);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 105);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexTimes.m"),
                  "resolved", "resolved", 105);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372554360U), "fileTimeLo",
                  "fileTimeLo", 105);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 105);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 105);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 105);
  sf_mex_assign(&c1_rhs105, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs105, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs105), "rhs", "rhs",
                  105);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs105), "lhs", "lhs",
                  105);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 106);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 106);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 106);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 106);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372553616U), "fileTimeLo",
                  "fileTimeLo", 106);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 106);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 106);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 106);
  sf_mex_assign(&c1_rhs106, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs106, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs106), "rhs", "rhs",
                  106);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs106), "lhs", "lhs",
                  106);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"), "context",
                  "context", 107);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 107);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 107);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 107);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372554360U), "fileTimeLo",
                  "fileTimeLo", 107);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 107);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 107);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 107);
  sf_mex_assign(&c1_rhs107, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs107, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs107), "rhs", "rhs",
                  107);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs107), "lhs", "lhs",
                  107);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 108);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_ixamax"), "name", "name",
                  108);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 108);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m"),
                  "resolved", "resolved", 108);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 108);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 108);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 108);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 108);
  sf_mex_assign(&c1_rhs108, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs108, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs108), "rhs", "rhs",
                  108);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs108), "lhs", "lhs",
                  108);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m"),
                  "context", "context", 109);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 109);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 109);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 109);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 109);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 109);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 109);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 109);
  sf_mex_assign(&c1_rhs109, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs109, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs109), "rhs", "rhs",
                  109);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs109), "lhs", "lhs",
                  109);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m"),
                  "context", "context", 110);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.ixamax"),
                  "name", "name", 110);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 110);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p"),
                  "resolved", "resolved", 110);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 110);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 110);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 110);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 110);
  sf_mex_assign(&c1_rhs110, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs110, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs110), "rhs", "rhs",
                  110);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs110), "lhs", "lhs",
                  110);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p"),
                  "context", "context", 111);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 111);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 111);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 111);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 111);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 111);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 111);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 111);
  sf_mex_assign(&c1_rhs111, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs111, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs111), "rhs", "rhs",
                  111);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs111), "lhs", "lhs",
                  111);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p!below_threshold"),
                  "context", "context", 112);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 112);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 112);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 112);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 112);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 112);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 112);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 112);
  sf_mex_assign(&c1_rhs112, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs112, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs112), "rhs", "rhs",
                  112);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs112), "lhs", "lhs",
                  112);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p!below_threshold"),
                  "context", "context", 113);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("length"), "name", "name", 113);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 113);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 113);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1303117406U), "fileTimeLo",
                  "fileTimeLo", 113);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 113);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 113);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 113);
  sf_mex_assign(&c1_rhs113, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs113, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs113), "rhs", "rhs",
                  113);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs113), "lhs", "lhs",
                  113);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m!intlength"),
                  "context", "context", 114);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 114);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 114);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 114);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323134578U), "fileTimeLo",
                  "fileTimeLo", 114);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 114);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 114);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 114);
  sf_mex_assign(&c1_rhs114, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs114, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs114), "rhs", "rhs",
                  114);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs114), "lhs", "lhs",
                  114);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p"),
                  "context", "context", 115);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.refblas.ixamax"),
                  "name", "name", 115);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 115);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/ixamax.p"),
                  "resolved", "resolved", 115);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 115);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 115);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 115);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 115);
  sf_mex_assign(&c1_rhs115, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs115, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs115), "rhs", "rhs",
                  115);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs115), "lhs", "lhs",
                  115);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/ixamax.p"),
                  "context", "context", 116);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.refblas.xcabs1"),
                  "name", "name", 116);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 116);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xcabs1.p"),
                  "resolved", "resolved", 116);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 116);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 116);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 116);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 116);
  sf_mex_assign(&c1_rhs116, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs116, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs116), "rhs", "rhs",
                  116);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs116), "lhs", "lhs",
                  116);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xcabs1.p"),
                  "context", "context", 117);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("abs"), "name", "name", 117);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 117);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 117);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363677852U), "fileTimeLo",
                  "fileTimeLo", 117);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 117);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 117);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 117);
  sf_mex_assign(&c1_rhs117, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs117, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs117), "rhs", "rhs",
                  117);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs117), "lhs", "lhs",
                  117);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 118);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 118);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 118);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 118);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363678556U), "fileTimeLo",
                  "fileTimeLo", 118);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 118);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 118);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 118);
  sf_mex_assign(&c1_rhs118, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs118, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs118), "rhs", "rhs",
                  118);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs118), "lhs", "lhs",
                  118);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 119);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_abs"), "name",
                  "name", 119);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 119);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "resolved", "resolved", 119);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286786312U), "fileTimeLo",
                  "fileTimeLo", 119);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 119);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 119);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 119);
  sf_mex_assign(&c1_rhs119, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs119, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs119), "rhs", "rhs",
                  119);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs119), "lhs", "lhs",
                  119);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/ixamax.p"),
                  "context", "context", 120);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 120);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 120);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 120);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 120);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 120);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 120);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 120);
  sf_mex_assign(&c1_rhs120, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs120, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs120), "rhs", "rhs",
                  120);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs120), "lhs", "lhs",
                  120);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/ixamax.p"),
                  "context", "context", 121);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 121);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 121);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 121);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372554360U), "fileTimeLo",
                  "fileTimeLo", 121);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 121);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 121);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 121);
  sf_mex_assign(&c1_rhs121, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs121, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs121), "rhs", "rhs",
                  121);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs121), "lhs", "lhs",
                  121);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 122);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_xswap"), "name", "name",
                  122);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 122);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m"),
                  "resolved", "resolved", 122);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951892U), "fileTimeLo",
                  "fileTimeLo", 122);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 122);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 122);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 122);
  sf_mex_assign(&c1_rhs122, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs122, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs122), "rhs", "rhs",
                  122);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs122), "lhs", "lhs",
                  122);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m"), "context",
                  "context", 123);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 123);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 123);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 123);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 123);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 123);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 123);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 123);
  sf_mex_assign(&c1_rhs123, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs123, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs123), "rhs", "rhs",
                  123);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs123), "lhs", "lhs",
                  123);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m"), "context",
                  "context", 124);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.xswap"),
                  "name", "name", 124);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 124);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xswap.p"),
                  "resolved", "resolved", 124);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 124);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 124);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 124);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 124);
  sf_mex_assign(&c1_rhs124, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs124, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs124), "rhs", "rhs",
                  124);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs124), "lhs", "lhs",
                  124);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xswap.p"),
                  "context", "context", 125);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 125);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 125);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 125);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 125);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 125);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 125);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 125);
  sf_mex_assign(&c1_rhs125, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs125, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs125), "rhs", "rhs",
                  125);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs125), "lhs", "lhs",
                  125);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xswap.p!below_threshold"),
                  "context", "context", 126);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 126);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 126);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 126);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 126);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 126);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 126);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 126);
  sf_mex_assign(&c1_rhs126, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs126, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs126), "rhs", "rhs",
                  126);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs126), "lhs", "lhs",
                  126);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xswap.p"),
                  "context", "context", 127);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.refblas.xswap"),
                  "name", "name", 127);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 127);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xswap.p"),
                  "resolved", "resolved", 127);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 127);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 127);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 127);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 127);
  sf_mex_assign(&c1_rhs127, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs127, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs127), "rhs", "rhs",
                  127);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs127), "lhs", "lhs",
                  127);
  sf_mex_destroy(&c1_rhs64);
  sf_mex_destroy(&c1_lhs64);
  sf_mex_destroy(&c1_rhs65);
  sf_mex_destroy(&c1_lhs65);
  sf_mex_destroy(&c1_rhs66);
  sf_mex_destroy(&c1_lhs66);
  sf_mex_destroy(&c1_rhs67);
  sf_mex_destroy(&c1_lhs67);
  sf_mex_destroy(&c1_rhs68);
  sf_mex_destroy(&c1_lhs68);
  sf_mex_destroy(&c1_rhs69);
  sf_mex_destroy(&c1_lhs69);
  sf_mex_destroy(&c1_rhs70);
  sf_mex_destroy(&c1_lhs70);
  sf_mex_destroy(&c1_rhs71);
  sf_mex_destroy(&c1_lhs71);
  sf_mex_destroy(&c1_rhs72);
  sf_mex_destroy(&c1_lhs72);
  sf_mex_destroy(&c1_rhs73);
  sf_mex_destroy(&c1_lhs73);
  sf_mex_destroy(&c1_rhs74);
  sf_mex_destroy(&c1_lhs74);
  sf_mex_destroy(&c1_rhs75);
  sf_mex_destroy(&c1_lhs75);
  sf_mex_destroy(&c1_rhs76);
  sf_mex_destroy(&c1_lhs76);
  sf_mex_destroy(&c1_rhs77);
  sf_mex_destroy(&c1_lhs77);
  sf_mex_destroy(&c1_rhs78);
  sf_mex_destroy(&c1_lhs78);
  sf_mex_destroy(&c1_rhs79);
  sf_mex_destroy(&c1_lhs79);
  sf_mex_destroy(&c1_rhs80);
  sf_mex_destroy(&c1_lhs80);
  sf_mex_destroy(&c1_rhs81);
  sf_mex_destroy(&c1_lhs81);
  sf_mex_destroy(&c1_rhs82);
  sf_mex_destroy(&c1_lhs82);
  sf_mex_destroy(&c1_rhs83);
  sf_mex_destroy(&c1_lhs83);
  sf_mex_destroy(&c1_rhs84);
  sf_mex_destroy(&c1_lhs84);
  sf_mex_destroy(&c1_rhs85);
  sf_mex_destroy(&c1_lhs85);
  sf_mex_destroy(&c1_rhs86);
  sf_mex_destroy(&c1_lhs86);
  sf_mex_destroy(&c1_rhs87);
  sf_mex_destroy(&c1_lhs87);
  sf_mex_destroy(&c1_rhs88);
  sf_mex_destroy(&c1_lhs88);
  sf_mex_destroy(&c1_rhs89);
  sf_mex_destroy(&c1_lhs89);
  sf_mex_destroy(&c1_rhs90);
  sf_mex_destroy(&c1_lhs90);
  sf_mex_destroy(&c1_rhs91);
  sf_mex_destroy(&c1_lhs91);
  sf_mex_destroy(&c1_rhs92);
  sf_mex_destroy(&c1_lhs92);
  sf_mex_destroy(&c1_rhs93);
  sf_mex_destroy(&c1_lhs93);
  sf_mex_destroy(&c1_rhs94);
  sf_mex_destroy(&c1_lhs94);
  sf_mex_destroy(&c1_rhs95);
  sf_mex_destroy(&c1_lhs95);
  sf_mex_destroy(&c1_rhs96);
  sf_mex_destroy(&c1_lhs96);
  sf_mex_destroy(&c1_rhs97);
  sf_mex_destroy(&c1_lhs97);
  sf_mex_destroy(&c1_rhs98);
  sf_mex_destroy(&c1_lhs98);
  sf_mex_destroy(&c1_rhs99);
  sf_mex_destroy(&c1_lhs99);
  sf_mex_destroy(&c1_rhs100);
  sf_mex_destroy(&c1_lhs100);
  sf_mex_destroy(&c1_rhs101);
  sf_mex_destroy(&c1_lhs101);
  sf_mex_destroy(&c1_rhs102);
  sf_mex_destroy(&c1_lhs102);
  sf_mex_destroy(&c1_rhs103);
  sf_mex_destroy(&c1_lhs103);
  sf_mex_destroy(&c1_rhs104);
  sf_mex_destroy(&c1_lhs104);
  sf_mex_destroy(&c1_rhs105);
  sf_mex_destroy(&c1_lhs105);
  sf_mex_destroy(&c1_rhs106);
  sf_mex_destroy(&c1_lhs106);
  sf_mex_destroy(&c1_rhs107);
  sf_mex_destroy(&c1_lhs107);
  sf_mex_destroy(&c1_rhs108);
  sf_mex_destroy(&c1_lhs108);
  sf_mex_destroy(&c1_rhs109);
  sf_mex_destroy(&c1_lhs109);
  sf_mex_destroy(&c1_rhs110);
  sf_mex_destroy(&c1_lhs110);
  sf_mex_destroy(&c1_rhs111);
  sf_mex_destroy(&c1_lhs111);
  sf_mex_destroy(&c1_rhs112);
  sf_mex_destroy(&c1_lhs112);
  sf_mex_destroy(&c1_rhs113);
  sf_mex_destroy(&c1_lhs113);
  sf_mex_destroy(&c1_rhs114);
  sf_mex_destroy(&c1_lhs114);
  sf_mex_destroy(&c1_rhs115);
  sf_mex_destroy(&c1_lhs115);
  sf_mex_destroy(&c1_rhs116);
  sf_mex_destroy(&c1_lhs116);
  sf_mex_destroy(&c1_rhs117);
  sf_mex_destroy(&c1_lhs117);
  sf_mex_destroy(&c1_rhs118);
  sf_mex_destroy(&c1_lhs118);
  sf_mex_destroy(&c1_rhs119);
  sf_mex_destroy(&c1_lhs119);
  sf_mex_destroy(&c1_rhs120);
  sf_mex_destroy(&c1_lhs120);
  sf_mex_destroy(&c1_rhs121);
  sf_mex_destroy(&c1_lhs121);
  sf_mex_destroy(&c1_rhs122);
  sf_mex_destroy(&c1_lhs122);
  sf_mex_destroy(&c1_rhs123);
  sf_mex_destroy(&c1_lhs123);
  sf_mex_destroy(&c1_rhs124);
  sf_mex_destroy(&c1_lhs124);
  sf_mex_destroy(&c1_rhs125);
  sf_mex_destroy(&c1_lhs125);
  sf_mex_destroy(&c1_rhs126);
  sf_mex_destroy(&c1_lhs126);
  sf_mex_destroy(&c1_rhs127);
  sf_mex_destroy(&c1_lhs127);
}

static void c1_c_info_helper(const mxArray **c1_info)
{
  const mxArray *c1_rhs128 = NULL;
  const mxArray *c1_lhs128 = NULL;
  const mxArray *c1_rhs129 = NULL;
  const mxArray *c1_lhs129 = NULL;
  const mxArray *c1_rhs130 = NULL;
  const mxArray *c1_lhs130 = NULL;
  const mxArray *c1_rhs131 = NULL;
  const mxArray *c1_lhs131 = NULL;
  const mxArray *c1_rhs132 = NULL;
  const mxArray *c1_lhs132 = NULL;
  const mxArray *c1_rhs133 = NULL;
  const mxArray *c1_lhs133 = NULL;
  const mxArray *c1_rhs134 = NULL;
  const mxArray *c1_lhs134 = NULL;
  const mxArray *c1_rhs135 = NULL;
  const mxArray *c1_lhs135 = NULL;
  const mxArray *c1_rhs136 = NULL;
  const mxArray *c1_lhs136 = NULL;
  const mxArray *c1_rhs137 = NULL;
  const mxArray *c1_lhs137 = NULL;
  const mxArray *c1_rhs138 = NULL;
  const mxArray *c1_lhs138 = NULL;
  const mxArray *c1_rhs139 = NULL;
  const mxArray *c1_lhs139 = NULL;
  const mxArray *c1_rhs140 = NULL;
  const mxArray *c1_lhs140 = NULL;
  const mxArray *c1_rhs141 = NULL;
  const mxArray *c1_lhs141 = NULL;
  const mxArray *c1_rhs142 = NULL;
  const mxArray *c1_lhs142 = NULL;
  const mxArray *c1_rhs143 = NULL;
  const mxArray *c1_lhs143 = NULL;
  const mxArray *c1_rhs144 = NULL;
  const mxArray *c1_lhs144 = NULL;
  const mxArray *c1_rhs145 = NULL;
  const mxArray *c1_lhs145 = NULL;
  const mxArray *c1_rhs146 = NULL;
  const mxArray *c1_lhs146 = NULL;
  const mxArray *c1_rhs147 = NULL;
  const mxArray *c1_lhs147 = NULL;
  const mxArray *c1_rhs148 = NULL;
  const mxArray *c1_lhs148 = NULL;
  const mxArray *c1_rhs149 = NULL;
  const mxArray *c1_lhs149 = NULL;
  const mxArray *c1_rhs150 = NULL;
  const mxArray *c1_lhs150 = NULL;
  const mxArray *c1_rhs151 = NULL;
  const mxArray *c1_lhs151 = NULL;
  const mxArray *c1_rhs152 = NULL;
  const mxArray *c1_lhs152 = NULL;
  const mxArray *c1_rhs153 = NULL;
  const mxArray *c1_lhs153 = NULL;
  const mxArray *c1_rhs154 = NULL;
  const mxArray *c1_lhs154 = NULL;
  const mxArray *c1_rhs155 = NULL;
  const mxArray *c1_lhs155 = NULL;
  const mxArray *c1_rhs156 = NULL;
  const mxArray *c1_lhs156 = NULL;
  const mxArray *c1_rhs157 = NULL;
  const mxArray *c1_lhs157 = NULL;
  const mxArray *c1_rhs158 = NULL;
  const mxArray *c1_lhs158 = NULL;
  const mxArray *c1_rhs159 = NULL;
  const mxArray *c1_lhs159 = NULL;
  const mxArray *c1_rhs160 = NULL;
  const mxArray *c1_lhs160 = NULL;
  const mxArray *c1_rhs161 = NULL;
  const mxArray *c1_lhs161 = NULL;
  const mxArray *c1_rhs162 = NULL;
  const mxArray *c1_lhs162 = NULL;
  const mxArray *c1_rhs163 = NULL;
  const mxArray *c1_lhs163 = NULL;
  const mxArray *c1_rhs164 = NULL;
  const mxArray *c1_lhs164 = NULL;
  const mxArray *c1_rhs165 = NULL;
  const mxArray *c1_lhs165 = NULL;
  const mxArray *c1_rhs166 = NULL;
  const mxArray *c1_lhs166 = NULL;
  const mxArray *c1_rhs167 = NULL;
  const mxArray *c1_lhs167 = NULL;
  const mxArray *c1_rhs168 = NULL;
  const mxArray *c1_lhs168 = NULL;
  const mxArray *c1_rhs169 = NULL;
  const mxArray *c1_lhs169 = NULL;
  const mxArray *c1_rhs170 = NULL;
  const mxArray *c1_lhs170 = NULL;
  const mxArray *c1_rhs171 = NULL;
  const mxArray *c1_lhs171 = NULL;
  const mxArray *c1_rhs172 = NULL;
  const mxArray *c1_lhs172 = NULL;
  const mxArray *c1_rhs173 = NULL;
  const mxArray *c1_lhs173 = NULL;
  const mxArray *c1_rhs174 = NULL;
  const mxArray *c1_lhs174 = NULL;
  const mxArray *c1_rhs175 = NULL;
  const mxArray *c1_lhs175 = NULL;
  const mxArray *c1_rhs176 = NULL;
  const mxArray *c1_lhs176 = NULL;
  const mxArray *c1_rhs177 = NULL;
  const mxArray *c1_lhs177 = NULL;
  const mxArray *c1_rhs178 = NULL;
  const mxArray *c1_lhs178 = NULL;
  const mxArray *c1_rhs179 = NULL;
  const mxArray *c1_lhs179 = NULL;
  const mxArray *c1_rhs180 = NULL;
  const mxArray *c1_lhs180 = NULL;
  const mxArray *c1_rhs181 = NULL;
  const mxArray *c1_lhs181 = NULL;
  const mxArray *c1_rhs182 = NULL;
  const mxArray *c1_lhs182 = NULL;
  const mxArray *c1_rhs183 = NULL;
  const mxArray *c1_lhs183 = NULL;
  const mxArray *c1_rhs184 = NULL;
  const mxArray *c1_lhs184 = NULL;
  const mxArray *c1_rhs185 = NULL;
  const mxArray *c1_lhs185 = NULL;
  const mxArray *c1_rhs186 = NULL;
  const mxArray *c1_lhs186 = NULL;
  const mxArray *c1_rhs187 = NULL;
  const mxArray *c1_lhs187 = NULL;
  const mxArray *c1_rhs188 = NULL;
  const mxArray *c1_lhs188 = NULL;
  const mxArray *c1_rhs189 = NULL;
  const mxArray *c1_lhs189 = NULL;
  const mxArray *c1_rhs190 = NULL;
  const mxArray *c1_lhs190 = NULL;
  const mxArray *c1_rhs191 = NULL;
  const mxArray *c1_lhs191 = NULL;
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xswap.p"),
                  "context", "context", 128);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("abs"), "name", "name", 128);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 128);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 128);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363677852U), "fileTimeLo",
                  "fileTimeLo", 128);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 128);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 128);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 128);
  sf_mex_assign(&c1_rhs128, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs128, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs128), "rhs", "rhs",
                  128);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs128), "lhs", "lhs",
                  128);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 129);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 129);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 129);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 129);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363678556U), "fileTimeLo",
                  "fileTimeLo", 129);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 129);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 129);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 129);
  sf_mex_assign(&c1_rhs129, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs129, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs129), "rhs", "rhs",
                  129);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs129), "lhs", "lhs",
                  129);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 130);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_abs"), "name",
                  "name", 130);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 130);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "resolved", "resolved", 130);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286786312U), "fileTimeLo",
                  "fileTimeLo", 130);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 130);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 130);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 130);
  sf_mex_assign(&c1_rhs130, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs130, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs130), "rhs", "rhs",
                  130);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs130), "lhs", "lhs",
                  130);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xswap.p"),
                  "context", "context", 131);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 131);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 131);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 131);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 131);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 131);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 131);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 131);
  sf_mex_assign(&c1_rhs131, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs131, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs131), "rhs", "rhs",
                  131);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs131), "lhs", "lhs",
                  131);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xswap.p"),
                  "context", "context", 132);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 132);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 132);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 132);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372554360U), "fileTimeLo",
                  "fileTimeLo", 132);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 132);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 132);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 132);
  sf_mex_assign(&c1_rhs132, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs132, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs132), "rhs", "rhs",
                  132);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs132), "lhs", "lhs",
                  132);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 133);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_div"), "name", "name", 133);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 133);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 133);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 133);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 133);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 133);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 133);
  sf_mex_assign(&c1_rhs133, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs133, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs133), "rhs", "rhs",
                  133);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs133), "lhs", "lhs",
                  133);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 134);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_xgeru"), "name", "name",
                  134);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 134);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m"),
                  "resolved", "resolved", 134);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951890U), "fileTimeLo",
                  "fileTimeLo", 134);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 134);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 134);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 134);
  sf_mex_assign(&c1_rhs134, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs134, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs134), "rhs", "rhs",
                  134);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs134), "lhs", "lhs",
                  134);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m"), "context",
                  "context", 135);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 135);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 135);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 135);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 135);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 135);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 135);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 135);
  sf_mex_assign(&c1_rhs135, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs135, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs135), "rhs", "rhs",
                  135);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs135), "lhs", "lhs",
                  135);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m"), "context",
                  "context", 136);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.xgeru"),
                  "name", "name", 136);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 136);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgeru.p"),
                  "resolved", "resolved", 136);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 136);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 136);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 136);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 136);
  sf_mex_assign(&c1_rhs136, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs136, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs136), "rhs", "rhs",
                  136);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs136), "lhs", "lhs",
                  136);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgeru.p"),
                  "context", "context", 137);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.xger"),
                  "name", "name", 137);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 137);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p"),
                  "resolved", "resolved", 137);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 137);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 137);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 137);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 137);
  sf_mex_assign(&c1_rhs137, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs137, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs137), "rhs", "rhs",
                  137);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs137), "lhs", "lhs",
                  137);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p"),
                  "context", "context", 138);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 138);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 138);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 138);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 138);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 138);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 138);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 138);
  sf_mex_assign(&c1_rhs138, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs138, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs138), "rhs", "rhs",
                  138);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs138), "lhs", "lhs",
                  138);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p!below_threshold"),
                  "context", "context", 139);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 139);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 139);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 139);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 139);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 139);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 139);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 139);
  sf_mex_assign(&c1_rhs139, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs139, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs139), "rhs", "rhs",
                  139);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs139), "lhs", "lhs",
                  139);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p!below_threshold"),
                  "context", "context", 140);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.int"),
                  "name", "name", 140);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 140);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/int.p"),
                  "resolved", "resolved", 140);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 140);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 140);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 140);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 140);
  sf_mex_assign(&c1_rhs140, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs140, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs140), "rhs", "rhs",
                  140);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs140), "lhs", "lhs",
                  140);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p!below_threshold"),
                  "context", "context", 141);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmax"), "name", "name", 141);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 141);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 141);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362225882U), "fileTimeLo",
                  "fileTimeLo", 141);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 141);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 141);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 141);
  sf_mex_assign(&c1_rhs141, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs141, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs141), "rhs", "rhs",
                  141);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs141), "lhs", "lhs",
                  141);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p!below_threshold"),
                  "context", "context", 142);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("min"), "name", "name", 142);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 142);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 142);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1311226518U), "fileTimeLo",
                  "fileTimeLo", 142);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 142);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 142);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 142);
  sf_mex_assign(&c1_rhs142, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs142, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs142), "rhs", "rhs",
                  142);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs142), "lhs", "lhs",
                  142);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 143);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 143);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 143);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 143);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 143);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 143);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 143);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 143);
  sf_mex_assign(&c1_rhs143, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs143, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs143), "rhs", "rhs",
                  143);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs143), "lhs", "lhs",
                  143);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 144);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 144);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 144);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 144);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 144);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 144);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 144);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 144);
  sf_mex_assign(&c1_rhs144, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs144, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs144), "rhs", "rhs",
                  144);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs144), "lhs", "lhs",
                  144);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 145);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 145);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 145);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 145);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 145);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 145);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 145);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 145);
  sf_mex_assign(&c1_rhs145, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs145, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs145), "rhs", "rhs",
                  145);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs145), "lhs", "lhs",
                  145);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 146);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 146);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 146);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 146);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363678556U), "fileTimeLo",
                  "fileTimeLo", 146);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 146);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 146);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 146);
  sf_mex_assign(&c1_rhs146, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs146, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs146), "rhs", "rhs",
                  146);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs146), "lhs", "lhs",
                  146);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p"),
                  "context", "context", 147);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.refblas.xger"),
                  "name", "name", 147);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 147);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xger.p"),
                  "resolved", "resolved", 147);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 147);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 147);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 147);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 147);
  sf_mex_assign(&c1_rhs147, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs147, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs147), "rhs", "rhs",
                  147);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs147), "lhs", "lhs",
                  147);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xger.p"),
                  "context", "context", 148);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.refblas.xgerx"),
                  "name", "name", 148);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 148);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "resolved", "resolved", 148);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 148);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 148);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 148);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 148);
  sf_mex_assign(&c1_rhs148, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs148, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs148), "rhs", "rhs",
                  148);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs148), "lhs", "lhs",
                  148);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 149);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("abs"), "name", "name", 149);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 149);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 149);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363677852U), "fileTimeLo",
                  "fileTimeLo", 149);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 149);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 149);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 149);
  sf_mex_assign(&c1_rhs149, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs149, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs149), "rhs", "rhs",
                  149);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs149), "lhs", "lhs",
                  149);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 150);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 150);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 150);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 150);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372554360U), "fileTimeLo",
                  "fileTimeLo", 150);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 150);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 150);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 150);
  sf_mex_assign(&c1_rhs150, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs150, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs150), "rhs", "rhs",
                  150);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs150), "lhs", "lhs",
                  150);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 151);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 151);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 151);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 151);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 151);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 151);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 151);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 151);
  sf_mex_assign(&c1_rhs151, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs151, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs151), "rhs", "rhs",
                  151);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs151), "lhs", "lhs",
                  151);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 152);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 152);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 152);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 152);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372554360U), "fileTimeLo",
                  "fileTimeLo", 152);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 152);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 152);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 152);
  sf_mex_assign(&c1_rhs152, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs152, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs152), "rhs", "rhs",
                  152);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs152), "lhs", "lhs",
                  152);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 153);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 153);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 153);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 153);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372554360U), "fileTimeLo",
                  "fileTimeLo", 153);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 153);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 153);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 153);
  sf_mex_assign(&c1_rhs153, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs153, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs153), "rhs", "rhs",
                  153);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs153), "lhs", "lhs",
                  153);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN"), "context",
                  "context", 154);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_ipiv2perm"), "name",
                  "name", 154);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 154);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_ipiv2perm.m"), "resolved",
                  "resolved", 154);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286786382U), "fileTimeLo",
                  "fileTimeLo", 154);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 154);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 154);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 154);
  sf_mex_assign(&c1_rhs154, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs154, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs154), "rhs", "rhs",
                  154);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs154), "lhs", "lhs",
                  154);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_ipiv2perm.m"), "context",
                  "context", 155);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("colon"), "name", "name", 155);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 155);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 155);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1378267188U), "fileTimeLo",
                  "fileTimeLo", 155);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 155);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 155);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 155);
  sf_mex_assign(&c1_rhs155, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs155, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs155), "rhs", "rhs",
                  155);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs155), "lhs", "lhs",
                  155);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_ipiv2perm.m"), "context",
                  "context", 156);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 156);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 156);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 156);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323134578U), "fileTimeLo",
                  "fileTimeLo", 156);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 156);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 156);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 156);
  sf_mex_assign(&c1_rhs156, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs156, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs156), "rhs", "rhs",
                  156);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs156), "lhs", "lhs",
                  156);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_ipiv2perm.m"), "context",
                  "context", 157);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexIntRelop"),
                  "name", "name", 157);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 157);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m"),
                  "resolved", "resolved", 157);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1326692322U), "fileTimeLo",
                  "fileTimeLo", 157);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 157);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 157);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 157);
  sf_mex_assign(&c1_rhs157, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs157, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs157), "rhs", "rhs",
                  157);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs157), "lhs", "lhs",
                  157);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN"), "context",
                  "context", 158);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 158);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 158);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 158);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 158);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 158);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 158);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 158);
  sf_mex_assign(&c1_rhs158, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs158, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs158), "rhs", "rhs",
                  158);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs158), "lhs", "lhs",
                  158);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN"), "context",
                  "context", 159);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 159);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 159);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 159);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372553616U), "fileTimeLo",
                  "fileTimeLo", 159);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 159);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 159);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 159);
  sf_mex_assign(&c1_rhs159, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs159, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs159), "rhs", "rhs",
                  159);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs159), "lhs", "lhs",
                  159);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN"), "context",
                  "context", 160);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 160);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 160);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 160);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 160);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 160);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 160);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 160);
  sf_mex_assign(&c1_rhs160, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs160, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs160), "rhs", "rhs",
                  160);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs160), "lhs", "lhs",
                  160);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN"), "context",
                  "context", 161);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_xtrsm"), "name", "name",
                  161);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 161);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m"),
                  "resolved", "resolved", 161);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951892U), "fileTimeLo",
                  "fileTimeLo", 161);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 161);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 161);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 161);
  sf_mex_assign(&c1_rhs161, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs161, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs161), "rhs", "rhs",
                  161);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs161), "lhs", "lhs",
                  161);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m"), "context",
                  "context", 162);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 162);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 162);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 162);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 162);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 162);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 162);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 162);
  sf_mex_assign(&c1_rhs162, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs162, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs162), "rhs", "rhs",
                  162);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs162), "lhs", "lhs",
                  162);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m"), "context",
                  "context", 163);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.xtrsm"),
                  "name", "name", 163);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 163);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xtrsm.p"),
                  "resolved", "resolved", 163);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 163);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 163);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 163);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 163);
  sf_mex_assign(&c1_rhs163, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs163, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs163), "rhs", "rhs",
                  163);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs163), "lhs", "lhs",
                  163);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xtrsm.p"),
                  "context", "context", 164);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 164);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 164);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 164);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 164);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 164);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 164);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 164);
  sf_mex_assign(&c1_rhs164, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs164, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs164), "rhs", "rhs",
                  164);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs164), "lhs", "lhs",
                  164);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xtrsm.p!below_threshold"),
                  "context", "context", 165);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 165);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 165);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 165);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 165);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 165);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 165);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 165);
  sf_mex_assign(&c1_rhs165, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs165, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs165), "rhs", "rhs",
                  165);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs165), "lhs", "lhs",
                  165);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xtrsm.p"),
                  "context", "context", 166);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 166);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 166);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 166);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271920U), "fileTimeLo",
                  "fileTimeLo", 166);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 166);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 166);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 166);
  sf_mex_assign(&c1_rhs166, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs166, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs166), "rhs", "rhs",
                  166);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs166), "lhs", "lhs",
                  166);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xtrsm.p"),
                  "context", "context", 167);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.refblas.xtrsm"),
                  "name", "name", 167);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 167);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xtrsm.p"),
                  "resolved", "resolved", 167);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271922U), "fileTimeLo",
                  "fileTimeLo", 167);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 167);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 167);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 167);
  sf_mex_assign(&c1_rhs167, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs167, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs167), "rhs", "rhs",
                  167);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs167), "lhs", "lhs",
                  167);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xtrsm.p"),
                  "context", "context", 168);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 168);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 168);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 168);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363678556U), "fileTimeLo",
                  "fileTimeLo", 168);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 168);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 168);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 168);
  sf_mex_assign(&c1_rhs168, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs168, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs168), "rhs", "rhs",
                  168);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs168), "lhs", "lhs",
                  168);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xtrsm.p"),
                  "context", "context", 169);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 169);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 169);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 169);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1389271920U), "fileTimeLo",
                  "fileTimeLo", 169);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 169);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 169);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 169);
  sf_mex_assign(&c1_rhs169, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs169, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs169), "rhs", "rhs",
                  169);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs169), "lhs", "lhs",
                  169);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xtrsm.p"),
                  "context", "context", 170);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 170);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 170);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 170);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 170);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 170);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 170);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 170);
  sf_mex_assign(&c1_rhs170, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs170, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs170), "rhs", "rhs",
                  170);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs170), "lhs", "lhs",
                  170);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 171);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmin"), "name", "name", 171);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 171);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 171);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362225882U), "fileTimeLo",
                  "fileTimeLo", 171);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 171);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 171);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 171);
  sf_mex_assign(&c1_rhs171, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs171, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs171), "rhs", "rhs",
                  171);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs171), "lhs", "lhs",
                  171);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xtrsm.p"),
                  "context", "context", 172);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("rdivide"), "name", "name", 172);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 172);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 172);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363677880U), "fileTimeLo",
                  "fileTimeLo", 172);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 172);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 172);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 172);
  sf_mex_assign(&c1_rhs172, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs172, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs172), "rhs", "rhs",
                  172);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs172), "lhs", "lhs",
                  172);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond"),
                  "context", "context", 173);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("norm"), "name", "name", 173);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 173);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m"), "resolved",
                  "resolved", 173);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363677868U), "fileTimeLo",
                  "fileTimeLo", 173);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 173);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 173);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 173);
  sf_mex_assign(&c1_rhs173, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs173, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs173), "rhs", "rhs",
                  173);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs173), "lhs", "lhs",
                  173);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m"), "context",
                  "context", 174);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 174);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 174);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 174);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363678556U), "fileTimeLo",
                  "fileTimeLo", 174);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 174);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 174);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 174);
  sf_mex_assign(&c1_rhs174, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs174, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs174), "rhs", "rhs",
                  174);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs174), "lhs", "lhs",
                  174);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm"),
                  "context", "context", 175);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("abs"), "name", "name", 175);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 175);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 175);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363677852U), "fileTimeLo",
                  "fileTimeLo", 175);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 175);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 175);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 175);
  sf_mex_assign(&c1_rhs175, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs175, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs175), "rhs", "rhs",
                  175);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs175), "lhs", "lhs",
                  175);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm"),
                  "context", "context", 176);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("isnan"), "name", "name", 176);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 176);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "resolved",
                  "resolved", 176);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363677858U), "fileTimeLo",
                  "fileTimeLo", 176);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 176);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 176);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 176);
  sf_mex_assign(&c1_rhs176, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs176, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs176), "rhs", "rhs",
                  176);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs176), "lhs", "lhs",
                  176);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "context",
                  "context", 177);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 177);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 177);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 177);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363678556U), "fileTimeLo",
                  "fileTimeLo", 177);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 177);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 177);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 177);
  sf_mex_assign(&c1_rhs177, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs177, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs177), "rhs", "rhs",
                  177);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs177), "lhs", "lhs",
                  177);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm"),
                  "context", "context", 178);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_guarded_nan"), "name",
                  "name", 178);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 178);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m"),
                  "resolved", "resolved", 178);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286786376U), "fileTimeLo",
                  "fileTimeLo", 178);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 178);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 178);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 178);
  sf_mex_assign(&c1_rhs178, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs178, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs178), "rhs", "rhs",
                  178);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs178), "lhs", "lhs",
                  178);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m"),
                  "context", "context", 179);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_is_float_class"), "name",
                  "name", 179);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 179);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m"),
                  "resolved", "resolved", 179);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286786382U), "fileTimeLo",
                  "fileTimeLo", 179);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 179);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 179);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 179);
  sf_mex_assign(&c1_rhs179, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs179, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs179), "rhs", "rhs",
                  179);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs179), "lhs", "lhs",
                  179);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond"),
                  "context", "context", 180);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_warning"), "name", "name",
                  180);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 180);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m"), "resolved",
                  "resolved", 180);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286786402U), "fileTimeLo",
                  "fileTimeLo", 180);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 180);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 180);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 180);
  sf_mex_assign(&c1_rhs180, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs180, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs180), "rhs", "rhs",
                  180);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs180), "lhs", "lhs",
                  180);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond"),
                  "context", "context", 181);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("isnan"), "name", "name", 181);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 181);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "resolved",
                  "resolved", 181);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363677858U), "fileTimeLo",
                  "fileTimeLo", 181);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 181);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 181);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 181);
  sf_mex_assign(&c1_rhs181, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs181, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs181), "rhs", "rhs",
                  181);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs181), "lhs", "lhs",
                  181);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond"),
                  "context", "context", 182);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eps"), "name", "name", 182);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 182);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "resolved",
                  "resolved", 182);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1326691996U), "fileTimeLo",
                  "fileTimeLo", 182);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 182);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 182);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 182);
  sf_mex_assign(&c1_rhs182, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs182, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs182), "rhs", "rhs",
                  182);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs182), "lhs", "lhs",
                  182);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond"),
                  "context", "context", 183);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_flt2str"), "name", "name",
                  183);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 183);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m"), "resolved",
                  "resolved", 183);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1360246350U), "fileTimeLo",
                  "fileTimeLo", 183);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 183);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 183);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 183);
  sf_mex_assign(&c1_rhs183, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs183, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs183), "rhs", "rhs",
                  183);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs183), "lhs", "lhs",
                  183);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m"), "context",
                  "context", 184);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "name", "name", 184);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 184);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/char.m"), "resolved",
                  "resolved", 184);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1319697568U), "fileTimeLo",
                  "fileTimeLo", 184);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 184);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 184);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 184);
  sf_mex_assign(&c1_rhs184, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs184, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs184), "rhs", "rhs",
                  184);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs184), "lhs", "lhs",
                  184);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Rudaba/Documents/PHD TAKE 2/Simulations/AircraftModelling/simulateEKF_smallerStateVec.m"),
                  "context", "context", 185);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("diag"), "name", "name", 185);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 185);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m"), "resolved",
                  "resolved", 185);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363677854U), "fileTimeLo",
                  "fileTimeLo", 185);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 185);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 185);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 185);
  sf_mex_assign(&c1_rhs185, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs185, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs185), "rhs", "rhs",
                  185);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs185), "lhs", "lhs",
                  185);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m"), "context",
                  "context", 186);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("ismatrix"), "name", "name",
                  186);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 186);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ismatrix.m"), "resolved",
                  "resolved", 186);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1331268858U), "fileTimeLo",
                  "fileTimeLo", 186);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 186);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 186);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 186);
  sf_mex_assign(&c1_rhs186, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs186, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs186), "rhs", "rhs",
                  186);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs186), "lhs", "lhs",
                  186);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m"), "context",
                  "context", 187);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 187);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 187);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 187);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323134578U), "fileTimeLo",
                  "fileTimeLo", 187);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 187);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 187);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 187);
  sf_mex_assign(&c1_rhs187, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs187, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs187), "rhs", "rhs",
                  187);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs187), "lhs", "lhs",
                  187);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m"), "context",
                  "context", 188);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("isequal"), "name", "name", 188);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 188);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "resolved",
                  "resolved", 188);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286786358U), "fileTimeLo",
                  "fileTimeLo", 188);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 188);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 188);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 188);
  sf_mex_assign(&c1_rhs188, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs188, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs188), "rhs", "rhs",
                  188);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs188), "lhs", "lhs",
                  188);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "context",
                  "context", 189);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_isequal_core"), "name",
                  "name", 189);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 189);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m"),
                  "resolved", "resolved", 189);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286786386U), "fileTimeLo",
                  "fileTimeLo", 189);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 189);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 189);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 189);
  sf_mex_assign(&c1_rhs189, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs189, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs189), "rhs", "rhs",
                  189);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs189), "lhs", "lhs",
                  189);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar"),
                  "context", "context", 190);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("isnan"), "name", "name", 190);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 190);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "resolved",
                  "resolved", 190);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363677858U), "fileTimeLo",
                  "fileTimeLo", 190);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 190);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 190);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 190);
  sf_mex_assign(&c1_rhs190, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs190, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs190), "rhs", "rhs",
                  190);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs190), "lhs", "lhs",
                  190);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m!calclen"), "context",
                  "context", 191);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 191);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 191);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 191);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323134578U), "fileTimeLo",
                  "fileTimeLo", 191);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 191);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 191);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 191);
  sf_mex_assign(&c1_rhs191, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs191, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs191), "rhs", "rhs",
                  191);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs191), "lhs", "lhs",
                  191);
  sf_mex_destroy(&c1_rhs128);
  sf_mex_destroy(&c1_lhs128);
  sf_mex_destroy(&c1_rhs129);
  sf_mex_destroy(&c1_lhs129);
  sf_mex_destroy(&c1_rhs130);
  sf_mex_destroy(&c1_lhs130);
  sf_mex_destroy(&c1_rhs131);
  sf_mex_destroy(&c1_lhs131);
  sf_mex_destroy(&c1_rhs132);
  sf_mex_destroy(&c1_lhs132);
  sf_mex_destroy(&c1_rhs133);
  sf_mex_destroy(&c1_lhs133);
  sf_mex_destroy(&c1_rhs134);
  sf_mex_destroy(&c1_lhs134);
  sf_mex_destroy(&c1_rhs135);
  sf_mex_destroy(&c1_lhs135);
  sf_mex_destroy(&c1_rhs136);
  sf_mex_destroy(&c1_lhs136);
  sf_mex_destroy(&c1_rhs137);
  sf_mex_destroy(&c1_lhs137);
  sf_mex_destroy(&c1_rhs138);
  sf_mex_destroy(&c1_lhs138);
  sf_mex_destroy(&c1_rhs139);
  sf_mex_destroy(&c1_lhs139);
  sf_mex_destroy(&c1_rhs140);
  sf_mex_destroy(&c1_lhs140);
  sf_mex_destroy(&c1_rhs141);
  sf_mex_destroy(&c1_lhs141);
  sf_mex_destroy(&c1_rhs142);
  sf_mex_destroy(&c1_lhs142);
  sf_mex_destroy(&c1_rhs143);
  sf_mex_destroy(&c1_lhs143);
  sf_mex_destroy(&c1_rhs144);
  sf_mex_destroy(&c1_lhs144);
  sf_mex_destroy(&c1_rhs145);
  sf_mex_destroy(&c1_lhs145);
  sf_mex_destroy(&c1_rhs146);
  sf_mex_destroy(&c1_lhs146);
  sf_mex_destroy(&c1_rhs147);
  sf_mex_destroy(&c1_lhs147);
  sf_mex_destroy(&c1_rhs148);
  sf_mex_destroy(&c1_lhs148);
  sf_mex_destroy(&c1_rhs149);
  sf_mex_destroy(&c1_lhs149);
  sf_mex_destroy(&c1_rhs150);
  sf_mex_destroy(&c1_lhs150);
  sf_mex_destroy(&c1_rhs151);
  sf_mex_destroy(&c1_lhs151);
  sf_mex_destroy(&c1_rhs152);
  sf_mex_destroy(&c1_lhs152);
  sf_mex_destroy(&c1_rhs153);
  sf_mex_destroy(&c1_lhs153);
  sf_mex_destroy(&c1_rhs154);
  sf_mex_destroy(&c1_lhs154);
  sf_mex_destroy(&c1_rhs155);
  sf_mex_destroy(&c1_lhs155);
  sf_mex_destroy(&c1_rhs156);
  sf_mex_destroy(&c1_lhs156);
  sf_mex_destroy(&c1_rhs157);
  sf_mex_destroy(&c1_lhs157);
  sf_mex_destroy(&c1_rhs158);
  sf_mex_destroy(&c1_lhs158);
  sf_mex_destroy(&c1_rhs159);
  sf_mex_destroy(&c1_lhs159);
  sf_mex_destroy(&c1_rhs160);
  sf_mex_destroy(&c1_lhs160);
  sf_mex_destroy(&c1_rhs161);
  sf_mex_destroy(&c1_lhs161);
  sf_mex_destroy(&c1_rhs162);
  sf_mex_destroy(&c1_lhs162);
  sf_mex_destroy(&c1_rhs163);
  sf_mex_destroy(&c1_lhs163);
  sf_mex_destroy(&c1_rhs164);
  sf_mex_destroy(&c1_lhs164);
  sf_mex_destroy(&c1_rhs165);
  sf_mex_destroy(&c1_lhs165);
  sf_mex_destroy(&c1_rhs166);
  sf_mex_destroy(&c1_lhs166);
  sf_mex_destroy(&c1_rhs167);
  sf_mex_destroy(&c1_lhs167);
  sf_mex_destroy(&c1_rhs168);
  sf_mex_destroy(&c1_lhs168);
  sf_mex_destroy(&c1_rhs169);
  sf_mex_destroy(&c1_lhs169);
  sf_mex_destroy(&c1_rhs170);
  sf_mex_destroy(&c1_lhs170);
  sf_mex_destroy(&c1_rhs171);
  sf_mex_destroy(&c1_lhs171);
  sf_mex_destroy(&c1_rhs172);
  sf_mex_destroy(&c1_lhs172);
  sf_mex_destroy(&c1_rhs173);
  sf_mex_destroy(&c1_lhs173);
  sf_mex_destroy(&c1_rhs174);
  sf_mex_destroy(&c1_lhs174);
  sf_mex_destroy(&c1_rhs175);
  sf_mex_destroy(&c1_lhs175);
  sf_mex_destroy(&c1_rhs176);
  sf_mex_destroy(&c1_lhs176);
  sf_mex_destroy(&c1_rhs177);
  sf_mex_destroy(&c1_lhs177);
  sf_mex_destroy(&c1_rhs178);
  sf_mex_destroy(&c1_lhs178);
  sf_mex_destroy(&c1_rhs179);
  sf_mex_destroy(&c1_lhs179);
  sf_mex_destroy(&c1_rhs180);
  sf_mex_destroy(&c1_lhs180);
  sf_mex_destroy(&c1_rhs181);
  sf_mex_destroy(&c1_lhs181);
  sf_mex_destroy(&c1_rhs182);
  sf_mex_destroy(&c1_lhs182);
  sf_mex_destroy(&c1_rhs183);
  sf_mex_destroy(&c1_lhs183);
  sf_mex_destroy(&c1_rhs184);
  sf_mex_destroy(&c1_lhs184);
  sf_mex_destroy(&c1_rhs185);
  sf_mex_destroy(&c1_lhs185);
  sf_mex_destroy(&c1_rhs186);
  sf_mex_destroy(&c1_lhs186);
  sf_mex_destroy(&c1_rhs187);
  sf_mex_destroy(&c1_lhs187);
  sf_mex_destroy(&c1_rhs188);
  sf_mex_destroy(&c1_lhs188);
  sf_mex_destroy(&c1_rhs189);
  sf_mex_destroy(&c1_lhs189);
  sf_mex_destroy(&c1_rhs190);
  sf_mex_destroy(&c1_lhs190);
  sf_mex_destroy(&c1_rhs191);
  sf_mex_destroy(&c1_lhs191);
}

static void c1_d_info_helper(const mxArray **c1_info)
{
  const mxArray *c1_rhs192 = NULL;
  const mxArray *c1_lhs192 = NULL;
  const mxArray *c1_rhs193 = NULL;
  const mxArray *c1_lhs193 = NULL;
  const mxArray *c1_rhs194 = NULL;
  const mxArray *c1_lhs194 = NULL;
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m!calclen"), "context",
                  "context", 192);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("min"), "name", "name", 192);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 192);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 192);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1311226518U), "fileTimeLo",
                  "fileTimeLo", 192);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 192);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 192);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 192);
  sf_mex_assign(&c1_rhs192, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs192, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs192), "rhs", "rhs",
                  192);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs192), "lhs", "lhs",
                  192);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m"), "context",
                  "context", 193);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 193);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 193);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 193);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 193);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 193);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 193);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 193);
  sf_mex_assign(&c1_rhs193, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs193, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs193), "rhs", "rhs",
                  193);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs193), "lhs", "lhs",
                  193);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m"), "context",
                  "context", 194);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 194);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 194);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 194);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375951888U), "fileTimeLo",
                  "fileTimeLo", 194);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 194);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 194);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 194);
  sf_mex_assign(&c1_rhs194, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs194, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs194), "rhs", "rhs",
                  194);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs194), "lhs", "lhs",
                  194);
  sf_mex_destroy(&c1_rhs192);
  sf_mex_destroy(&c1_lhs192);
  sf_mex_destroy(&c1_rhs193);
  sf_mex_destroy(&c1_lhs193);
  sf_mex_destroy(&c1_rhs194);
  sf_mex_destroy(&c1_lhs194);
}

static real_T c1_mpower(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_a)
{
  return c1_power(chartInstance, c1_a);
}

static real_T c1_power(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_a)
{
  real_T c1_b_a;
  real_T c1_ak;
  real_T c1_c_a;
  c1_b_a = c1_a;
  c1_eml_scalar_eg(chartInstance);
  c1_ak = c1_b_a;
  c1_c_a = c1_ak;
  c1_eml_scalar_eg(chartInstance);
  return c1_c_a * c1_c_a;
}

static void c1_eml_scalar_eg(SFc1_aircraftControl_smallerStateEKFInstanceStruct *
  chartInstance)
{
  (void)chartInstance;
}

static void c1_eml_switch_helper
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_b_eml_switch_helper
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_b_power(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_a[361], real_T c1_y[361])
{
  int32_T c1_k;
  real_T c1_b_k;
  real_T c1_ak;
  real_T c1_b_a;
  real_T c1_b_y;
  for (c1_k = 0; c1_k < 361; c1_k++) {
    c1_b_k = 1.0 + (real_T)c1_k;
    c1_ak = c1_a[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      c1_b_k), 1, 361, 1, 0) - 1];
    c1_b_a = c1_ak;
    c1_eml_scalar_eg(chartInstance);
    c1_b_y = c1_b_a * c1_b_a;
    c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", c1_b_k),
      1, 361, 1, 0) - 1] = c1_b_y;
  }
}

static void c1_eye(SFc1_aircraftControl_smallerStateEKFInstanceStruct
                   *chartInstance, real_T c1_I[361])
{
  int32_T c1_i185;
  int32_T c1_k;
  int32_T c1_b_k;
  (void)chartInstance;
  for (c1_i185 = 0; c1_i185 < 361; c1_i185++) {
    c1_I[c1_i185] = 0.0;
  }

  for (c1_k = 1; c1_k < 20; c1_k++) {
    c1_b_k = c1_k;
    c1_I[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c1_b_k), 1, 19, 1, 0) + 19 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c1_b_k), 1, 19, 2, 0) - 1))
      - 1] = 1.0;
  }
}

static real_T c1_b_mpower(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_a)
{
  real_T c1_b_a;
  real_T c1_c_a;
  real_T c1_ak;
  real_T c1_d_a;
  real_T c1_ar;
  c1_b_a = c1_a;
  c1_c_a = c1_b_a;
  c1_eml_scalar_eg(chartInstance);
  c1_ak = c1_c_a;
  c1_d_a = c1_ak;
  c1_eml_scalar_eg(chartInstance);
  c1_ar = c1_d_a;
  return muDoubleScalarPower(c1_ar, 3.0);
}

static real_T c1_c_mpower(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_a)
{
  real_T c1_b_a;
  real_T c1_c_a;
  real_T c1_ak;
  real_T c1_d_a;
  real_T c1_ar;
  c1_b_a = c1_a;
  c1_c_a = c1_b_a;
  c1_eml_scalar_eg(chartInstance);
  c1_ak = c1_c_a;
  c1_d_a = c1_ak;
  c1_eml_scalar_eg(chartInstance);
  c1_ar = c1_d_a;
  return muDoubleScalarPower(c1_ar, 4.0);
}

static void c1_b_eml_scalar_eg
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[361], real_T c1_B[361], real_T c1_C[361], real_T
  c1_b_C[361])
{
  int32_T c1_i186;
  int32_T c1_i187;
  real_T c1_b_A[361];
  int32_T c1_i188;
  real_T c1_b_B[361];
  for (c1_i186 = 0; c1_i186 < 361; c1_i186++) {
    c1_b_C[c1_i186] = c1_C[c1_i186];
  }

  for (c1_i187 = 0; c1_i187 < 361; c1_i187++) {
    c1_b_A[c1_i187] = c1_A[c1_i187];
  }

  for (c1_i188 = 0; c1_i188 < 361; c1_i188++) {
    c1_b_B[c1_i188] = c1_B[c1_i188];
  }

  c1_g_eml_xgemm(chartInstance, c1_b_A, c1_b_B, c1_b_C);
}

static void c1_threshold(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c1_c_eml_scalar_eg
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_b_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[114], real_T c1_B[361], real_T c1_C[114], real_T
  c1_b_C[114])
{
  int32_T c1_i189;
  int32_T c1_i190;
  real_T c1_b_A[114];
  int32_T c1_i191;
  real_T c1_b_B[361];
  for (c1_i189 = 0; c1_i189 < 114; c1_i189++) {
    c1_b_C[c1_i189] = c1_C[c1_i189];
  }

  for (c1_i190 = 0; c1_i190 < 114; c1_i190++) {
    c1_b_A[c1_i190] = c1_A[c1_i190];
  }

  for (c1_i191 = 0; c1_i191 < 361; c1_i191++) {
    c1_b_B[c1_i191] = c1_B[c1_i191];
  }

  c1_h_eml_xgemm(chartInstance, c1_b_A, c1_b_B, c1_b_C);
}

static void c1_d_eml_scalar_eg
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_c_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[114], real_T c1_B[114], real_T c1_C[36], real_T
  c1_b_C[36])
{
  int32_T c1_i192;
  int32_T c1_i193;
  real_T c1_b_A[114];
  int32_T c1_i194;
  real_T c1_b_B[114];
  for (c1_i192 = 0; c1_i192 < 36; c1_i192++) {
    c1_b_C[c1_i192] = c1_C[c1_i192];
  }

  for (c1_i193 = 0; c1_i193 < 114; c1_i193++) {
    c1_b_A[c1_i193] = c1_A[c1_i193];
  }

  for (c1_i194 = 0; c1_i194 < 114; c1_i194++) {
    c1_b_B[c1_i194] = c1_B[c1_i194];
  }

  c1_i_eml_xgemm(chartInstance, c1_b_A, c1_b_B, c1_b_C);
}

static void c1_e_eml_scalar_eg
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_f_eml_scalar_eg
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_d_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[361], real_T c1_B[114], real_T c1_C[114], real_T
  c1_b_C[114])
{
  int32_T c1_i195;
  int32_T c1_i196;
  real_T c1_b_A[361];
  int32_T c1_i197;
  real_T c1_b_B[114];
  for (c1_i195 = 0; c1_i195 < 114; c1_i195++) {
    c1_b_C[c1_i195] = c1_C[c1_i195];
  }

  for (c1_i196 = 0; c1_i196 < 361; c1_i196++) {
    c1_b_A[c1_i196] = c1_A[c1_i196];
  }

  for (c1_i197 = 0; c1_i197 < 114; c1_i197++) {
    c1_b_B[c1_i197] = c1_B[c1_i197];
  }

  c1_j_eml_xgemm(chartInstance, c1_b_A, c1_b_B, c1_b_C);
}

static void c1_inv(SFc1_aircraftControl_smallerStateEKFInstanceStruct
                   *chartInstance, real_T c1_x[36], real_T c1_y[36])
{
  int32_T c1_i198;
  real_T c1_b_x[36];
  int32_T c1_i199;
  int32_T c1_info;
  int32_T c1_ipiv[6];
  int32_T c1_i200;
  int32_T c1_b_ipiv[6];
  int32_T c1_k;
  int32_T c1_b_k;
  int32_T c1_c;
  int32_T c1_c_k;
  int32_T c1_a;
  int32_T c1_b_a;
  boolean_T c1_overflow;
  int32_T c1_j;
  int32_T c1_b_j;
  int32_T c1_c_a;
  int32_T c1_d_a;
  int32_T c1_i201;
  int32_T c1_e_a;
  int32_T c1_f_a;
  boolean_T c1_b_overflow;
  int32_T c1_i;
  int32_T c1_b_i;
  int32_T c1_i202;
  real_T c1_c_x[36];
  int32_T c1_i203;
  real_T c1_d_x[36];
  real_T c1_n1x;
  int32_T c1_i204;
  real_T c1_b_y[36];
  real_T c1_n1xinv;
  real_T c1_rc;
  real_T c1_e_x;
  boolean_T c1_b;
  real_T c1_f_x;
  int32_T c1_i205;
  static char_T c1_cv1[8] = { '%', '%', '%', 'd', '.', '%', 'd', 'e' };

  char_T c1_u[8];
  const mxArray *c1_c_y = NULL;
  real_T c1_b_u;
  const mxArray *c1_d_y = NULL;
  real_T c1_c_u;
  const mxArray *c1_e_y = NULL;
  real_T c1_d_u;
  const mxArray *c1_f_y = NULL;
  char_T c1_str[14];
  int32_T c1_i206;
  char_T c1_b_str[14];
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T guard3 = false;
  for (c1_i198 = 0; c1_i198 < 36; c1_i198++) {
    c1_b_x[c1_i198] = c1_x[c1_i198];
  }

  for (c1_i199 = 0; c1_i199 < 36; c1_i199++) {
    c1_y[c1_i199] = 0.0;
  }

  c1_b_eml_matlab_zgetrf(chartInstance, c1_b_x, c1_ipiv, &c1_info);
  for (c1_i200 = 0; c1_i200 < 6; c1_i200++) {
    c1_b_ipiv[c1_i200] = c1_ipiv[c1_i200];
  }

  c1_eml_ipiv2perm(chartInstance, c1_b_ipiv, c1_ipiv);
  for (c1_k = 1; c1_k < 7; c1_k++) {
    c1_b_k = c1_k;
    c1_c = c1_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
      "", (real_T)c1_b_k), 1, 6, 1, 0) - 1];
    c1_y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c1_b_k), 1, 6, 1, 0) + 6 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c1_c), 1, 6, 2, 0) - 1)) - 1]
      = 1.0;
    c1_c_k = c1_b_k;
    c1_a = c1_c_k;
    c1_b_a = c1_a;
    if (c1_b_a > 6) {
      c1_overflow = false;
    } else {
      c1_eml_switch_helper(chartInstance);
      c1_overflow = false;
    }

    if (c1_overflow) {
      c1_check_forloop_overflow_error(chartInstance, c1_overflow);
    }

    for (c1_j = c1_c_k; c1_j < 7; c1_j++) {
      c1_b_j = c1_j;
      if (c1_y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
             (real_T)c1_b_j), 1, 6, 1, 0) + 6 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
             (int32_T)_SFD_INTEGER_CHECK("", (real_T)c1_c), 1, 6, 2, 0) - 1)) -
          1] != 0.0) {
        c1_c_a = c1_b_j;
        c1_d_a = c1_c_a + 1;
        c1_i201 = c1_d_a;
        c1_e_a = c1_i201;
        c1_f_a = c1_e_a;
        if (c1_f_a > 6) {
          c1_b_overflow = false;
        } else {
          c1_eml_switch_helper(chartInstance);
          c1_b_overflow = false;
        }

        if (c1_b_overflow) {
          c1_check_forloop_overflow_error(chartInstance, c1_b_overflow);
        }

        for (c1_i = c1_i201; c1_i < 7; c1_i++) {
          c1_b_i = c1_i;
          c1_y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                  (real_T)c1_b_i), 1, 6, 1, 0) + 6 *
                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                   (real_T)c1_c), 1, 6, 2, 0) - 1)) - 1] = c1_y
            [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c1_b_i), 1, 6, 1, 0) + 6 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c1_c), 1, 6, 2, 0) -
               1)) - 1] - c1_y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c1_b_j), 1, 6, 1, 0) + 6 *
                                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c1_c), 1, 6, 2, 0) - 1)) - 1] *
            c1_b_x[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                      "", (real_T)c1_b_i), 1, 6, 1, 0) + 6 *
                    (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", (real_T)c1_b_j), 1, 6, 2, 0) - 1)) - 1];
        }
      }
    }
  }

  for (c1_i202 = 0; c1_i202 < 36; c1_i202++) {
    c1_c_x[c1_i202] = c1_b_x[c1_i202];
  }

  c1_b_eml_xtrsm(chartInstance, c1_c_x, c1_y);
  for (c1_i203 = 0; c1_i203 < 36; c1_i203++) {
    c1_d_x[c1_i203] = c1_x[c1_i203];
  }

  c1_n1x = c1_norm(chartInstance, c1_d_x);
  for (c1_i204 = 0; c1_i204 < 36; c1_i204++) {
    c1_b_y[c1_i204] = c1_y[c1_i204];
  }

  c1_n1xinv = c1_norm(chartInstance, c1_b_y);
  c1_rc = 1.0 / (c1_n1x * c1_n1xinv);
  guard1 = false;
  guard2 = false;
  if (c1_n1x == 0.0) {
    guard2 = true;
  } else if (c1_n1xinv == 0.0) {
    guard2 = true;
  } else if (c1_rc == 0.0) {
    guard1 = true;
  } else {
    c1_e_x = c1_rc;
    c1_b = muDoubleScalarIsNaN(c1_e_x);
    guard3 = false;
    if (c1_b) {
      guard3 = true;
    } else {
      c1_eps(chartInstance);
      if (c1_rc < 2.2204460492503131E-16) {
        guard3 = true;
      }
    }

    if (guard3 == true) {
      c1_f_x = c1_rc;
      for (c1_i205 = 0; c1_i205 < 8; c1_i205++) {
        c1_u[c1_i205] = c1_cv1[c1_i205];
      }

      c1_c_y = NULL;
      sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 8),
                    false);
      c1_b_u = 14.0;
      c1_d_y = NULL;
      sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0),
                    false);
      c1_c_u = 6.0;
      c1_e_y = NULL;
      sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_c_u, 0, 0U, 0U, 0U, 0),
                    false);
      c1_d_u = c1_f_x;
      c1_f_y = NULL;
      sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_d_u, 0, 0U, 0U, 0U, 0),
                    false);
      c1_emlrt_marshallIn(chartInstance, sf_mex_call_debug
                          (sfGlobalDebugInstanceStruct, "sprintf", 1U, 2U, 14,
                           sf_mex_call_debug(sfGlobalDebugInstanceStruct,
        "sprintf", 1U, 3U, 14, c1_c_y, 14, c1_d_y, 14, c1_e_y), 14, c1_f_y),
                          "sprintf", c1_str);
      for (c1_i206 = 0; c1_i206 < 14; c1_i206++) {
        c1_b_str[c1_i206] = c1_str[c1_i206];
      }

      c1_b_eml_warning(chartInstance, c1_b_str);
    }
  }

  if (guard2 == true) {
    guard1 = true;
  }

  if (guard1 == true) {
    c1_eml_warning(chartInstance);
  }
}

static void c1_eps(SFc1_aircraftControl_smallerStateEKFInstanceStruct
                   *chartInstance)
{
  (void)chartInstance;
}

static void c1_eml_matlab_zgetrf
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, real_T
   c1_A[36], real_T c1_b_A[36], int32_T c1_ipiv[6], int32_T *c1_info)
{
  int32_T c1_i207;
  for (c1_i207 = 0; c1_i207 < 36; c1_i207++) {
    c1_b_A[c1_i207] = c1_A[c1_i207];
  }

  c1_b_eml_matlab_zgetrf(chartInstance, c1_b_A, c1_ipiv, c1_info);
}

static int32_T c1_eml_ixamax(SFc1_aircraftControl_smallerStateEKFInstanceStruct *
  chartInstance, int32_T c1_n, real_T c1_x[36], int32_T c1_ix0)
{
  int32_T c1_idxmax;
  int32_T c1_b_n;
  int32_T c1_b_ix0;
  int32_T c1_c_n;
  int32_T c1_c_ix0;
  int32_T c1_ix;
  real_T c1_b_x;
  real_T c1_c_x;
  real_T c1_d_x;
  real_T c1_y;
  real_T c1_e_x;
  real_T c1_f_x;
  real_T c1_b_y;
  real_T c1_smax;
  int32_T c1_d_n;
  int32_T c1_b;
  int32_T c1_b_b;
  boolean_T c1_overflow;
  int32_T c1_k;
  int32_T c1_b_k;
  int32_T c1_a;
  real_T c1_g_x;
  real_T c1_h_x;
  real_T c1_i_x;
  real_T c1_c_y;
  real_T c1_j_x;
  real_T c1_k_x;
  real_T c1_d_y;
  real_T c1_s;
  c1_b_n = c1_n;
  c1_b_ix0 = c1_ix0;
  c1_c_n = c1_b_n;
  c1_c_ix0 = c1_b_ix0;
  if (c1_c_n < 1) {
    c1_idxmax = 0;
  } else {
    c1_idxmax = 1;
    if (c1_c_n > 1) {
      c1_ix = c1_c_ix0;
      c1_b_x = c1_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", (real_T)c1_ix), 1, 36, 1, 0) - 1];
      c1_c_x = c1_b_x;
      c1_d_x = c1_c_x;
      c1_y = muDoubleScalarAbs(c1_d_x);
      c1_e_x = 0.0;
      c1_f_x = c1_e_x;
      c1_b_y = muDoubleScalarAbs(c1_f_x);
      c1_smax = c1_y + c1_b_y;
      c1_d_n = c1_c_n;
      c1_b = c1_d_n;
      c1_b_b = c1_b;
      if (2 > c1_b_b) {
        c1_overflow = false;
      } else {
        c1_eml_switch_helper(chartInstance);
        c1_overflow = (c1_b_b > 2147483646);
      }

      if (c1_overflow) {
        c1_check_forloop_overflow_error(chartInstance, c1_overflow);
      }

      for (c1_k = 2; c1_k <= c1_d_n; c1_k++) {
        c1_b_k = c1_k;
        c1_a = c1_ix + 1;
        c1_ix = c1_a;
        c1_g_x = c1_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c1_ix), 1, 36, 1, 0) - 1];
        c1_h_x = c1_g_x;
        c1_i_x = c1_h_x;
        c1_c_y = muDoubleScalarAbs(c1_i_x);
        c1_j_x = 0.0;
        c1_k_x = c1_j_x;
        c1_d_y = muDoubleScalarAbs(c1_k_x);
        c1_s = c1_c_y + c1_d_y;
        if (c1_s > c1_smax) {
          c1_idxmax = c1_b_k;
          c1_smax = c1_s;
        }
      }
    }
  }

  return c1_idxmax;
}

static void c1_check_forloop_overflow_error
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, boolean_T
   c1_overflow)
{
  int32_T c1_i208;
  static char_T c1_cv2[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o', 'p',
    '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  char_T c1_u[34];
  const mxArray *c1_y = NULL;
  int32_T c1_i209;
  static char_T c1_cv3[23] = { 'c', 'o', 'd', 'e', 'r', '.', 'i', 'n', 't', 'e',
    'r', 'n', 'a', 'l', '.', 'i', 'n', 'd', 'e', 'x', 'I', 'n', 't' };

  char_T c1_b_u[23];
  const mxArray *c1_b_y = NULL;
  (void)chartInstance;
  if (!c1_overflow) {
  } else {
    for (c1_i208 = 0; c1_i208 < 34; c1_i208++) {
      c1_u[c1_i208] = c1_cv2[c1_i208];
    }

    c1_y = NULL;
    sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 34),
                  false);
    for (c1_i209 = 0; c1_i209 < 23; c1_i209++) {
      c1_b_u[c1_i209] = c1_cv3[c1_i209];
    }

    c1_b_y = NULL;
    sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1, 23),
                  false);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                      sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message",
      1U, 2U, 14, c1_y, 14, c1_b_y));
  }
}

static void c1_b_threshold(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c1_eml_xgeru(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, int32_T c1_m, int32_T c1_n, real_T c1_alpha1, int32_T c1_ix0,
  int32_T c1_iy0, real_T c1_A[36], int32_T c1_ia0, real_T c1_b_A[36])
{
  int32_T c1_i210;
  for (c1_i210 = 0; c1_i210 < 36; c1_i210++) {
    c1_b_A[c1_i210] = c1_A[c1_i210];
  }

  c1_b_eml_xgeru(chartInstance, c1_m, c1_n, c1_alpha1, c1_ix0, c1_iy0, c1_b_A,
                 c1_ia0);
}

static void c1_eml_ipiv2perm(SFc1_aircraftControl_smallerStateEKFInstanceStruct *
  chartInstance, int32_T c1_ipiv[6], int32_T c1_perm[6])
{
  int32_T c1_i211;
  int32_T c1_k;
  real_T c1_b_k;
  int32_T c1_ipk;
  int32_T c1_a;
  real_T c1_b;
  int32_T c1_b_a;
  real_T c1_b_b;
  int32_T c1_idx;
  real_T c1_flt;
  boolean_T c1_p;
  int32_T c1_pipk;
  for (c1_i211 = 0; c1_i211 < 6; c1_i211++) {
    c1_perm[c1_i211] = 1 + c1_i211;
  }

  for (c1_k = 0; c1_k < 5; c1_k++) {
    c1_b_k = 1.0 + (real_T)c1_k;
    c1_ipk = c1_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
      ("", c1_b_k), 1, 6, 1, 0) - 1];
    c1_a = c1_ipk;
    c1_b = c1_b_k;
    c1_b_a = c1_a;
    c1_b_b = c1_b;
    c1_b_eml_switch_helper(chartInstance);
    c1_idx = c1_b_a;
    c1_flt = c1_b_b;
    c1_p = ((real_T)c1_idx > c1_flt);
    if (c1_p) {
      c1_pipk = c1_perm[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c1_ipk), 1, 6, 1, 0) - 1];
      c1_perm[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c1_ipk), 1, 6, 1, 0) - 1] = c1_perm[_SFD_EML_ARRAY_BOUNDS_CHECK(
        "", (int32_T)_SFD_INTEGER_CHECK("", c1_b_k), 1, 6, 1, 0) - 1];
      c1_perm[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        c1_b_k), 1, 6, 1, 0) - 1] = c1_pipk;
    }
  }
}

static void c1_eml_xtrsm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[36], real_T c1_B[36], real_T c1_b_B[36])
{
  int32_T c1_i212;
  int32_T c1_i213;
  real_T c1_b_A[36];
  for (c1_i212 = 0; c1_i212 < 36; c1_i212++) {
    c1_b_B[c1_i212] = c1_B[c1_i212];
  }

  for (c1_i213 = 0; c1_i213 < 36; c1_i213++) {
    c1_b_A[c1_i213] = c1_A[c1_i213];
  }

  c1_b_eml_xtrsm(chartInstance, c1_b_A, c1_b_B);
}

static void c1_c_threshold(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static real_T c1_norm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
                      *chartInstance, real_T c1_x[36])
{
  real_T c1_y;
  int32_T c1_j;
  real_T c1_b_j;
  real_T c1_s;
  int32_T c1_i;
  real_T c1_b_i;
  real_T c1_b_x;
  real_T c1_c_x;
  real_T c1_b_y;
  real_T c1_d_x;
  boolean_T c1_b;
  boolean_T exitg1;
  (void)chartInstance;
  c1_y = 0.0;
  c1_j = 0;
  exitg1 = false;
  while ((exitg1 == false) && (c1_j < 6)) {
    c1_b_j = 1.0 + (real_T)c1_j;
    c1_s = 0.0;
    for (c1_i = 0; c1_i < 6; c1_i++) {
      c1_b_i = 1.0 + (real_T)c1_i;
      c1_b_x = c1_x[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", c1_b_i), 1, 6, 1, 0) + 6 *
                     (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c1_b_j), 1, 6, 2, 0) - 1)) - 1];
      c1_c_x = c1_b_x;
      c1_b_y = muDoubleScalarAbs(c1_c_x);
      c1_s += c1_b_y;
    }

    c1_d_x = c1_s;
    c1_b = muDoubleScalarIsNaN(c1_d_x);
    if (c1_b) {
      c1_y = rtNaN;
      exitg1 = true;
    } else {
      if (c1_s > c1_y) {
        c1_y = c1_s;
      }

      c1_j++;
    }
  }

  return c1_y;
}

static void c1_eml_warning(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance)
{
  int32_T c1_i214;
  static char_T c1_varargin_1[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a',
    't', 'r', 'i', 'x' };

  char_T c1_u[27];
  const mxArray *c1_y = NULL;
  (void)chartInstance;
  for (c1_i214 = 0; c1_i214 < 27; c1_i214++) {
    c1_u[c1_i214] = c1_varargin_1[c1_i214];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 27), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "warning", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    1U, 14, c1_y));
}

static void c1_b_eml_warning(SFc1_aircraftControl_smallerStateEKFInstanceStruct *
  chartInstance, char_T c1_varargin_2[14])
{
  int32_T c1_i215;
  static char_T c1_varargin_1[33] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'i', 'l', 'l', 'C', 'o', 'n', 'd', 'i', 't', 'i',
    'o', 'n', 'e', 'd', 'M', 'a', 't', 'r', 'i', 'x' };

  char_T c1_u[33];
  const mxArray *c1_y = NULL;
  int32_T c1_i216;
  char_T c1_b_u[14];
  const mxArray *c1_b_y = NULL;
  (void)chartInstance;
  for (c1_i215 = 0; c1_i215 < 33; c1_i215++) {
    c1_u[c1_i215] = c1_varargin_1[c1_i215];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 33), false);
  for (c1_i216 = 0; c1_i216 < 14; c1_i216++) {
    c1_b_u[c1_i216] = c1_varargin_2[c1_i216];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1, 14),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "warning", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    2U, 14, c1_y, 14, c1_b_y));
}

static void c1_g_eml_scalar_eg
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_e_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[114], real_T c1_B[36], real_T c1_C[114], real_T
  c1_b_C[114])
{
  int32_T c1_i217;
  int32_T c1_i218;
  real_T c1_b_A[114];
  int32_T c1_i219;
  real_T c1_b_B[36];
  for (c1_i217 = 0; c1_i217 < 114; c1_i217++) {
    c1_b_C[c1_i217] = c1_C[c1_i217];
  }

  for (c1_i218 = 0; c1_i218 < 114; c1_i218++) {
    c1_b_A[c1_i218] = c1_A[c1_i218];
  }

  for (c1_i219 = 0; c1_i219 < 36; c1_i219++) {
    c1_b_B[c1_i219] = c1_B[c1_i219];
  }

  c1_k_eml_xgemm(chartInstance, c1_b_A, c1_b_B, c1_b_C);
}

static void c1_h_eml_scalar_eg
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_i_eml_scalar_eg
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_f_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[114], real_T c1_B[114], real_T c1_C[361], real_T
  c1_b_C[361])
{
  int32_T c1_i220;
  int32_T c1_i221;
  real_T c1_b_A[114];
  int32_T c1_i222;
  real_T c1_b_B[114];
  for (c1_i220 = 0; c1_i220 < 361; c1_i220++) {
    c1_b_C[c1_i220] = c1_C[c1_i220];
  }

  for (c1_i221 = 0; c1_i221 < 114; c1_i221++) {
    c1_b_A[c1_i221] = c1_A[c1_i221];
  }

  for (c1_i222 = 0; c1_i222 < 114; c1_i222++) {
    c1_b_B[c1_i222] = c1_B[c1_i222];
  }

  c1_l_eml_xgemm(chartInstance, c1_b_A, c1_b_B, c1_b_C);
}

static void c1_diag(SFc1_aircraftControl_smallerStateEKFInstanceStruct
                    *chartInstance, real_T c1_v[361], real_T c1_d[19])
{
  int32_T c1_j;
  int32_T c1_b_j;
  (void)chartInstance;
  for (c1_j = 1; c1_j < 20; c1_j++) {
    c1_b_j = c1_j;
    c1_d[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c1_b_j), 1, 19, 1, 0) - 1] = c1_v[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)(1 + (c1_b_j - 1) * 20)), 1, 361, 1, 0) - 1];
  }
}

static void c1_b_diag(SFc1_aircraftControl_smallerStateEKFInstanceStruct
                      *chartInstance, real_T c1_v[36], real_T c1_d[6])
{
  int32_T c1_j;
  int32_T c1_b_j;
  (void)chartInstance;
  for (c1_j = 1; c1_j < 7; c1_j++) {
    c1_b_j = c1_j;
    c1_d[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c1_b_j), 1, 6, 1, 0) - 1] = c1_v[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)(1 + (c1_b_j - 1) * 7)), 1, 36, 1, 0) - 1];
  }
}

static const mxArray *c1_o_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static int32_T c1_w_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i223;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i223, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i223;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
    chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_w_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_x_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_b_is_active_c1_aircraftControl_smallerStateEKF, const char_T
   *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_y_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_aircraftControl_smallerStateEKF), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_aircraftControl_smallerStateEKF);
  return c1_y;
}

static uint8_T c1_y_emlrt_marshallIn
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, const
   mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_g_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[361], real_T c1_B[361], real_T c1_C[361])
{
  real_T c1_alpha1;
  real_T c1_beta1;
  char_T c1_TRANSB;
  char_T c1_TRANSA;
  ptrdiff_t c1_m_t;
  ptrdiff_t c1_n_t;
  ptrdiff_t c1_k_t;
  ptrdiff_t c1_lda_t;
  ptrdiff_t c1_ldb_t;
  ptrdiff_t c1_ldc_t;
  double * c1_alpha1_t;
  double * c1_Aia0_t;
  double * c1_Bib0_t;
  double * c1_beta1_t;
  double * c1_Cic0_t;
  c1_threshold(chartInstance);
  c1_alpha1 = 1.0;
  c1_beta1 = 0.0;
  c1_TRANSB = 'N';
  c1_TRANSA = 'N';
  c1_m_t = (ptrdiff_t)(19);
  c1_n_t = (ptrdiff_t)(19);
  c1_k_t = (ptrdiff_t)(19);
  c1_lda_t = (ptrdiff_t)(19);
  c1_ldb_t = (ptrdiff_t)(19);
  c1_ldc_t = (ptrdiff_t)(19);
  c1_alpha1_t = (double *)(&c1_alpha1);
  c1_Aia0_t = (double *)(&c1_A[0]);
  c1_Bib0_t = (double *)(&c1_B[0]);
  c1_beta1_t = (double *)(&c1_beta1);
  c1_Cic0_t = (double *)(&c1_C[0]);
  dgemm(&c1_TRANSA, &c1_TRANSB, &c1_m_t, &c1_n_t, &c1_k_t, c1_alpha1_t,
        c1_Aia0_t, &c1_lda_t, c1_Bib0_t, &c1_ldb_t, c1_beta1_t, c1_Cic0_t,
        &c1_ldc_t);
}

static void c1_h_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[114], real_T c1_B[361], real_T c1_C[114])
{
  real_T c1_alpha1;
  real_T c1_beta1;
  char_T c1_TRANSB;
  char_T c1_TRANSA;
  ptrdiff_t c1_m_t;
  ptrdiff_t c1_n_t;
  ptrdiff_t c1_k_t;
  ptrdiff_t c1_lda_t;
  ptrdiff_t c1_ldb_t;
  ptrdiff_t c1_ldc_t;
  double * c1_alpha1_t;
  double * c1_Aia0_t;
  double * c1_Bib0_t;
  double * c1_beta1_t;
  double * c1_Cic0_t;
  c1_threshold(chartInstance);
  c1_alpha1 = 1.0;
  c1_beta1 = 0.0;
  c1_TRANSB = 'N';
  c1_TRANSA = 'N';
  c1_m_t = (ptrdiff_t)(6);
  c1_n_t = (ptrdiff_t)(19);
  c1_k_t = (ptrdiff_t)(19);
  c1_lda_t = (ptrdiff_t)(6);
  c1_ldb_t = (ptrdiff_t)(19);
  c1_ldc_t = (ptrdiff_t)(6);
  c1_alpha1_t = (double *)(&c1_alpha1);
  c1_Aia0_t = (double *)(&c1_A[0]);
  c1_Bib0_t = (double *)(&c1_B[0]);
  c1_beta1_t = (double *)(&c1_beta1);
  c1_Cic0_t = (double *)(&c1_C[0]);
  dgemm(&c1_TRANSA, &c1_TRANSB, &c1_m_t, &c1_n_t, &c1_k_t, c1_alpha1_t,
        c1_Aia0_t, &c1_lda_t, c1_Bib0_t, &c1_ldb_t, c1_beta1_t, c1_Cic0_t,
        &c1_ldc_t);
}

static void c1_i_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[114], real_T c1_B[114], real_T c1_C[36])
{
  real_T c1_alpha1;
  real_T c1_beta1;
  char_T c1_TRANSB;
  char_T c1_TRANSA;
  ptrdiff_t c1_m_t;
  ptrdiff_t c1_n_t;
  ptrdiff_t c1_k_t;
  ptrdiff_t c1_lda_t;
  ptrdiff_t c1_ldb_t;
  ptrdiff_t c1_ldc_t;
  double * c1_alpha1_t;
  double * c1_Aia0_t;
  double * c1_Bib0_t;
  double * c1_beta1_t;
  double * c1_Cic0_t;
  c1_threshold(chartInstance);
  c1_alpha1 = 1.0;
  c1_beta1 = 0.0;
  c1_TRANSB = 'N';
  c1_TRANSA = 'N';
  c1_m_t = (ptrdiff_t)(6);
  c1_n_t = (ptrdiff_t)(6);
  c1_k_t = (ptrdiff_t)(19);
  c1_lda_t = (ptrdiff_t)(6);
  c1_ldb_t = (ptrdiff_t)(19);
  c1_ldc_t = (ptrdiff_t)(6);
  c1_alpha1_t = (double *)(&c1_alpha1);
  c1_Aia0_t = (double *)(&c1_A[0]);
  c1_Bib0_t = (double *)(&c1_B[0]);
  c1_beta1_t = (double *)(&c1_beta1);
  c1_Cic0_t = (double *)(&c1_C[0]);
  dgemm(&c1_TRANSA, &c1_TRANSB, &c1_m_t, &c1_n_t, &c1_k_t, c1_alpha1_t,
        c1_Aia0_t, &c1_lda_t, c1_Bib0_t, &c1_ldb_t, c1_beta1_t, c1_Cic0_t,
        &c1_ldc_t);
}

static void c1_j_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[361], real_T c1_B[114], real_T c1_C[114])
{
  real_T c1_alpha1;
  real_T c1_beta1;
  char_T c1_TRANSB;
  char_T c1_TRANSA;
  ptrdiff_t c1_m_t;
  ptrdiff_t c1_n_t;
  ptrdiff_t c1_k_t;
  ptrdiff_t c1_lda_t;
  ptrdiff_t c1_ldb_t;
  ptrdiff_t c1_ldc_t;
  double * c1_alpha1_t;
  double * c1_Aia0_t;
  double * c1_Bib0_t;
  double * c1_beta1_t;
  double * c1_Cic0_t;
  c1_threshold(chartInstance);
  c1_alpha1 = 1.0;
  c1_beta1 = 0.0;
  c1_TRANSB = 'N';
  c1_TRANSA = 'N';
  c1_m_t = (ptrdiff_t)(19);
  c1_n_t = (ptrdiff_t)(6);
  c1_k_t = (ptrdiff_t)(19);
  c1_lda_t = (ptrdiff_t)(19);
  c1_ldb_t = (ptrdiff_t)(19);
  c1_ldc_t = (ptrdiff_t)(19);
  c1_alpha1_t = (double *)(&c1_alpha1);
  c1_Aia0_t = (double *)(&c1_A[0]);
  c1_Bib0_t = (double *)(&c1_B[0]);
  c1_beta1_t = (double *)(&c1_beta1);
  c1_Cic0_t = (double *)(&c1_C[0]);
  dgemm(&c1_TRANSA, &c1_TRANSB, &c1_m_t, &c1_n_t, &c1_k_t, c1_alpha1_t,
        c1_Aia0_t, &c1_lda_t, c1_Bib0_t, &c1_ldb_t, c1_beta1_t, c1_Cic0_t,
        &c1_ldc_t);
}

static void c1_b_eml_matlab_zgetrf
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance, real_T
   c1_A[36], int32_T c1_ipiv[6], int32_T *c1_info)
{
  int32_T c1_i224;
  int32_T c1_j;
  int32_T c1_b_j;
  int32_T c1_a;
  int32_T c1_b_a;
  int32_T c1_jm1;
  int32_T c1_b;
  int32_T c1_b_b;
  int32_T c1_mmj;
  int32_T c1_c_a;
  int32_T c1_d_a;
  int32_T c1_c;
  int32_T c1_c_b;
  int32_T c1_d_b;
  int32_T c1_jj;
  int32_T c1_e_a;
  int32_T c1_f_a;
  int32_T c1_jp1j;
  int32_T c1_g_a;
  int32_T c1_h_a;
  int32_T c1_b_c;
  int32_T c1_i225;
  int32_T c1_i226;
  int32_T c1_i227;
  real_T c1_b_A[36];
  int32_T c1_i_a;
  int32_T c1_j_a;
  int32_T c1_jpiv_offset;
  int32_T c1_k_a;
  int32_T c1_e_b;
  int32_T c1_l_a;
  int32_T c1_f_b;
  int32_T c1_jpiv;
  int32_T c1_m_a;
  int32_T c1_g_b;
  int32_T c1_n_a;
  int32_T c1_h_b;
  int32_T c1_c_c;
  int32_T c1_i_b;
  int32_T c1_j_b;
  int32_T c1_jrow;
  int32_T c1_o_a;
  int32_T c1_k_b;
  int32_T c1_p_a;
  int32_T c1_l_b;
  int32_T c1_jprow;
  int32_T c1_ix0;
  int32_T c1_iy0;
  int32_T c1_b_ix0;
  int32_T c1_b_iy0;
  int32_T c1_c_ix0;
  int32_T c1_c_iy0;
  int32_T c1_ix;
  int32_T c1_iy;
  int32_T c1_k;
  real_T c1_temp;
  int32_T c1_q_a;
  int32_T c1_r_a;
  int32_T c1_b_jp1j;
  int32_T c1_s_a;
  int32_T c1_t_a;
  int32_T c1_d_c;
  int32_T c1_u_a;
  int32_T c1_m_b;
  int32_T c1_v_a;
  int32_T c1_n_b;
  int32_T c1_i228;
  int32_T c1_w_a;
  int32_T c1_o_b;
  int32_T c1_x_a;
  int32_T c1_p_b;
  boolean_T c1_overflow;
  int32_T c1_i;
  int32_T c1_b_i;
  real_T c1_x;
  real_T c1_y;
  real_T c1_b_x;
  real_T c1_b_y;
  real_T c1_z;
  int32_T c1_q_b;
  int32_T c1_r_b;
  int32_T c1_e_c;
  int32_T c1_y_a;
  int32_T c1_ab_a;
  int32_T c1_f_c;
  int32_T c1_bb_a;
  int32_T c1_cb_a;
  int32_T c1_g_c;
  real_T c1_d4;
  c1_eps(chartInstance);
  for (c1_i224 = 0; c1_i224 < 6; c1_i224++) {
    c1_ipiv[c1_i224] = 1 + c1_i224;
  }

  *c1_info = 0;
  for (c1_j = 1; c1_j < 6; c1_j++) {
    c1_b_j = c1_j;
    c1_a = c1_b_j;
    c1_b_a = c1_a - 1;
    c1_jm1 = c1_b_a;
    c1_b = c1_b_j;
    c1_b_b = c1_b;
    c1_mmj = 6 - c1_b_b;
    c1_c_a = c1_jm1;
    c1_d_a = c1_c_a;
    c1_c = c1_d_a * 7;
    c1_c_b = c1_c;
    c1_d_b = c1_c_b + 1;
    c1_jj = c1_d_b;
    c1_e_a = c1_jj;
    c1_f_a = c1_e_a + 1;
    c1_jp1j = c1_f_a;
    c1_g_a = c1_mmj;
    c1_h_a = c1_g_a;
    c1_b_c = c1_h_a;
    c1_i225 = 0;
    for (c1_i226 = 0; c1_i226 < 6; c1_i226++) {
      for (c1_i227 = 0; c1_i227 < 6; c1_i227++) {
        c1_b_A[c1_i227 + c1_i225] = c1_A[c1_i227 + c1_i225];
      }

      c1_i225 += 6;
    }

    c1_i_a = c1_eml_ixamax(chartInstance, c1_b_c + 1, c1_b_A, c1_jj);
    c1_j_a = c1_i_a - 1;
    c1_jpiv_offset = c1_j_a;
    c1_k_a = c1_jj;
    c1_e_b = c1_jpiv_offset;
    c1_l_a = c1_k_a;
    c1_f_b = c1_e_b;
    c1_jpiv = c1_l_a + c1_f_b;
    if (c1_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c1_jpiv), 1, 36, 1, 0) - 1] != 0.0) {
      if (c1_jpiv_offset != 0) {
        c1_m_a = c1_b_j;
        c1_g_b = c1_jpiv_offset;
        c1_n_a = c1_m_a;
        c1_h_b = c1_g_b;
        c1_c_c = c1_n_a + c1_h_b;
        c1_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c1_b_j), 1, 6, 1, 0) - 1] = c1_c_c;
        c1_i_b = c1_jm1;
        c1_j_b = c1_i_b + 1;
        c1_jrow = c1_j_b;
        c1_o_a = c1_jrow;
        c1_k_b = c1_jpiv_offset;
        c1_p_a = c1_o_a;
        c1_l_b = c1_k_b;
        c1_jprow = c1_p_a + c1_l_b;
        c1_ix0 = c1_jrow;
        c1_iy0 = c1_jprow;
        c1_b_ix0 = c1_ix0;
        c1_b_iy0 = c1_iy0;
        c1_b_threshold(chartInstance);
        c1_c_ix0 = c1_b_ix0;
        c1_c_iy0 = c1_b_iy0;
        c1_ix = c1_c_ix0;
        c1_iy = c1_c_iy0;
        for (c1_k = 1; c1_k < 7; c1_k++) {
          c1_temp = c1_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c1_ix), 1, 36, 1, 0) - 1];
          c1_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c1_ix), 1, 36, 1, 0) - 1] = c1_A[_SFD_EML_ARRAY_BOUNDS_CHECK
            ("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c1_iy), 1, 36, 1, 0) -
            1];
          c1_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c1_iy), 1, 36, 1, 0) - 1] = c1_temp;
          c1_q_a = c1_ix + 6;
          c1_ix = c1_q_a;
          c1_r_a = c1_iy + 6;
          c1_iy = c1_r_a;
        }
      }

      c1_b_jp1j = c1_jp1j;
      c1_s_a = c1_mmj;
      c1_t_a = c1_s_a;
      c1_d_c = c1_t_a;
      c1_u_a = c1_jp1j;
      c1_m_b = c1_d_c - 1;
      c1_v_a = c1_u_a;
      c1_n_b = c1_m_b;
      c1_i228 = c1_v_a + c1_n_b;
      c1_w_a = c1_b_jp1j;
      c1_o_b = c1_i228;
      c1_x_a = c1_w_a;
      c1_p_b = c1_o_b;
      if (c1_x_a > c1_p_b) {
        c1_overflow = false;
      } else {
        c1_eml_switch_helper(chartInstance);
        c1_overflow = (c1_p_b > 2147483646);
      }

      if (c1_overflow) {
        c1_check_forloop_overflow_error(chartInstance, c1_overflow);
      }

      for (c1_i = c1_b_jp1j; c1_i <= c1_i228; c1_i++) {
        c1_b_i = c1_i;
        c1_x = c1_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c1_b_i), 1, 36, 1, 0) - 1];
        c1_y = c1_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c1_jj), 1, 36, 1, 0) - 1];
        c1_b_x = c1_x;
        c1_b_y = c1_y;
        c1_z = c1_b_x / c1_b_y;
        c1_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c1_b_i), 1, 36, 1, 0) - 1] = c1_z;
      }
    } else {
      *c1_info = c1_b_j;
    }

    c1_q_b = c1_b_j;
    c1_r_b = c1_q_b;
    c1_e_c = 6 - c1_r_b;
    c1_y_a = c1_jj;
    c1_ab_a = c1_y_a;
    c1_f_c = c1_ab_a;
    c1_bb_a = c1_jj;
    c1_cb_a = c1_bb_a;
    c1_g_c = c1_cb_a;
    c1_d4 = -1.0;
    c1_b_eml_xgeru(chartInstance, c1_mmj, c1_e_c, c1_d4, c1_jp1j, c1_f_c + 6,
                   c1_A, c1_g_c + 7);
  }

  if (*c1_info == 0) {
    if (!(c1_A[35] != 0.0)) {
      *c1_info = 6;
    }
  }
}

static void c1_b_eml_xgeru(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, int32_T c1_m, int32_T c1_n, real_T c1_alpha1, int32_T c1_ix0,
  int32_T c1_iy0, real_T c1_A[36], int32_T c1_ia0)
{
  int32_T c1_b_m;
  int32_T c1_b_n;
  real_T c1_b_alpha1;
  int32_T c1_b_ix0;
  int32_T c1_b_iy0;
  int32_T c1_b_ia0;
  int32_T c1_c_m;
  int32_T c1_c_n;
  real_T c1_c_alpha1;
  int32_T c1_c_ix0;
  int32_T c1_c_iy0;
  int32_T c1_c_ia0;
  int32_T c1_d_m;
  int32_T c1_d_n;
  real_T c1_d_alpha1;
  int32_T c1_d_ix0;
  int32_T c1_d_iy0;
  int32_T c1_d_ia0;
  int32_T c1_e_m;
  int32_T c1_e_n;
  real_T c1_e_alpha1;
  int32_T c1_e_ix0;
  int32_T c1_e_iy0;
  int32_T c1_e_ia0;
  int32_T c1_ixstart;
  int32_T c1_a;
  int32_T c1_jA;
  int32_T c1_jy;
  int32_T c1_f_n;
  int32_T c1_b;
  int32_T c1_b_b;
  boolean_T c1_overflow;
  int32_T c1_j;
  real_T c1_yjy;
  real_T c1_temp;
  int32_T c1_ix;
  int32_T c1_c_b;
  int32_T c1_i229;
  int32_T c1_b_a;
  int32_T c1_d_b;
  int32_T c1_i230;
  int32_T c1_c_a;
  int32_T c1_e_b;
  int32_T c1_d_a;
  int32_T c1_f_b;
  boolean_T c1_b_overflow;
  int32_T c1_ijA;
  int32_T c1_b_ijA;
  int32_T c1_e_a;
  int32_T c1_f_a;
  int32_T c1_g_a;
  c1_b_m = c1_m;
  c1_b_n = c1_n;
  c1_b_alpha1 = c1_alpha1;
  c1_b_ix0 = c1_ix0;
  c1_b_iy0 = c1_iy0;
  c1_b_ia0 = c1_ia0;
  c1_c_m = c1_b_m;
  c1_c_n = c1_b_n;
  c1_c_alpha1 = c1_b_alpha1;
  c1_c_ix0 = c1_b_ix0;
  c1_c_iy0 = c1_b_iy0;
  c1_c_ia0 = c1_b_ia0;
  c1_d_m = c1_c_m;
  c1_d_n = c1_c_n;
  c1_d_alpha1 = c1_c_alpha1;
  c1_d_ix0 = c1_c_ix0;
  c1_d_iy0 = c1_c_iy0;
  c1_d_ia0 = c1_c_ia0;
  c1_e_m = c1_d_m;
  c1_e_n = c1_d_n;
  c1_e_alpha1 = c1_d_alpha1;
  c1_e_ix0 = c1_d_ix0;
  c1_e_iy0 = c1_d_iy0;
  c1_e_ia0 = c1_d_ia0;
  if (c1_e_alpha1 == 0.0) {
  } else {
    c1_ixstart = c1_e_ix0;
    c1_a = c1_e_ia0 - 1;
    c1_jA = c1_a;
    c1_jy = c1_e_iy0;
    c1_f_n = c1_e_n;
    c1_b = c1_f_n;
    c1_b_b = c1_b;
    if (1 > c1_b_b) {
      c1_overflow = false;
    } else {
      c1_eml_switch_helper(chartInstance);
      c1_overflow = (c1_b_b > 2147483646);
    }

    if (c1_overflow) {
      c1_check_forloop_overflow_error(chartInstance, c1_overflow);
    }

    for (c1_j = 1; c1_j <= c1_f_n; c1_j++) {
      c1_yjy = c1_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", (real_T)c1_jy), 1, 36, 1, 0) - 1];
      if (c1_yjy != 0.0) {
        c1_temp = c1_yjy * c1_e_alpha1;
        c1_ix = c1_ixstart;
        c1_c_b = c1_jA + 1;
        c1_i229 = c1_c_b;
        c1_b_a = c1_e_m;
        c1_d_b = c1_jA;
        c1_i230 = c1_b_a + c1_d_b;
        c1_c_a = c1_i229;
        c1_e_b = c1_i230;
        c1_d_a = c1_c_a;
        c1_f_b = c1_e_b;
        if (c1_d_a > c1_f_b) {
          c1_b_overflow = false;
        } else {
          c1_eml_switch_helper(chartInstance);
          c1_b_overflow = (c1_f_b > 2147483646);
        }

        if (c1_b_overflow) {
          c1_check_forloop_overflow_error(chartInstance, c1_b_overflow);
        }

        for (c1_ijA = c1_i229; c1_ijA <= c1_i230; c1_ijA++) {
          c1_b_ijA = c1_ijA;
          c1_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c1_b_ijA), 1, 36, 1, 0) - 1] =
            c1_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c1_b_ijA), 1, 36, 1, 0) - 1] +
            c1_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c1_ix), 1, 36, 1, 0) - 1] * c1_temp;
          c1_e_a = c1_ix + 1;
          c1_ix = c1_e_a;
        }
      }

      c1_f_a = c1_jy + 6;
      c1_jy = c1_f_a;
      c1_g_a = c1_jA + 6;
      c1_jA = c1_g_a;
    }
  }
}

static void c1_b_eml_xtrsm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[36], real_T c1_B[36])
{
  int32_T c1_j;
  int32_T c1_b_j;
  int32_T c1_jBcol;
  int32_T c1_k;
  int32_T c1_b_k;
  int32_T c1_kAcol;
  real_T c1_x;
  real_T c1_y;
  real_T c1_b_x;
  real_T c1_b_y;
  real_T c1_c_x;
  real_T c1_c_y;
  real_T c1_z;
  int32_T c1_i231;
  int32_T c1_b;
  int32_T c1_b_b;
  boolean_T c1_overflow;
  int32_T c1_i;
  int32_T c1_b_i;
  c1_c_threshold(chartInstance);
  for (c1_j = 1; c1_j < 7; c1_j++) {
    c1_b_j = c1_j - 1;
    c1_jBcol = 6 * c1_b_j;
    for (c1_k = 6; c1_k > 0; c1_k--) {
      c1_b_k = c1_k;
      c1_kAcol = 6 * (c1_b_k - 1);
      if (c1_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)(c1_b_k + c1_jBcol)), 1, 36, 1, 0) - 1] != 0.0) {
        c1_x = c1_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)(c1_b_k + c1_jBcol)), 1, 36, 1, 0) - 1];
        c1_y = c1_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)(c1_b_k + c1_kAcol)), 1, 36, 1, 0) - 1];
        c1_b_x = c1_x;
        c1_b_y = c1_y;
        c1_c_x = c1_b_x;
        c1_c_y = c1_b_y;
        c1_z = c1_c_x / c1_c_y;
        c1_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)(c1_b_k + c1_jBcol)), 1, 36, 1, 0) - 1] = c1_z;
        c1_i231 = c1_b_k - 1;
        c1_b = c1_i231;
        c1_b_b = c1_b;
        if (1 > c1_b_b) {
          c1_overflow = false;
        } else {
          c1_eml_switch_helper(chartInstance);
          c1_overflow = (c1_b_b > 2147483646);
        }

        if (c1_overflow) {
          c1_check_forloop_overflow_error(chartInstance, c1_overflow);
        }

        for (c1_i = 1; c1_i <= c1_i231; c1_i++) {
          c1_b_i = c1_i;
          c1_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)(c1_b_i + c1_jBcol)), 1, 36, 1, 0) - 1] =
            c1_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)(c1_b_i + c1_jBcol)), 1, 36, 1, 0) - 1] -
            c1_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)(c1_b_k + c1_jBcol)), 1, 36, 1, 0) - 1] *
            c1_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)(c1_b_i + c1_kAcol)), 1, 36, 1, 0) - 1];
        }
      }
    }
  }
}

static void c1_k_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[114], real_T c1_B[36], real_T c1_C[114])
{
  real_T c1_alpha1;
  real_T c1_beta1;
  char_T c1_TRANSB;
  char_T c1_TRANSA;
  ptrdiff_t c1_m_t;
  ptrdiff_t c1_n_t;
  ptrdiff_t c1_k_t;
  ptrdiff_t c1_lda_t;
  ptrdiff_t c1_ldb_t;
  ptrdiff_t c1_ldc_t;
  double * c1_alpha1_t;
  double * c1_Aia0_t;
  double * c1_Bib0_t;
  double * c1_beta1_t;
  double * c1_Cic0_t;
  c1_threshold(chartInstance);
  c1_alpha1 = 1.0;
  c1_beta1 = 0.0;
  c1_TRANSB = 'N';
  c1_TRANSA = 'N';
  c1_m_t = (ptrdiff_t)(19);
  c1_n_t = (ptrdiff_t)(6);
  c1_k_t = (ptrdiff_t)(6);
  c1_lda_t = (ptrdiff_t)(19);
  c1_ldb_t = (ptrdiff_t)(6);
  c1_ldc_t = (ptrdiff_t)(19);
  c1_alpha1_t = (double *)(&c1_alpha1);
  c1_Aia0_t = (double *)(&c1_A[0]);
  c1_Bib0_t = (double *)(&c1_B[0]);
  c1_beta1_t = (double *)(&c1_beta1);
  c1_Cic0_t = (double *)(&c1_C[0]);
  dgemm(&c1_TRANSA, &c1_TRANSB, &c1_m_t, &c1_n_t, &c1_k_t, c1_alpha1_t,
        c1_Aia0_t, &c1_lda_t, c1_Bib0_t, &c1_ldb_t, c1_beta1_t, c1_Cic0_t,
        &c1_ldc_t);
}

static void c1_l_eml_xgemm(SFc1_aircraftControl_smallerStateEKFInstanceStruct
  *chartInstance, real_T c1_A[114], real_T c1_B[114], real_T c1_C[361])
{
  real_T c1_alpha1;
  real_T c1_beta1;
  char_T c1_TRANSB;
  char_T c1_TRANSA;
  ptrdiff_t c1_m_t;
  ptrdiff_t c1_n_t;
  ptrdiff_t c1_k_t;
  ptrdiff_t c1_lda_t;
  ptrdiff_t c1_ldb_t;
  ptrdiff_t c1_ldc_t;
  double * c1_alpha1_t;
  double * c1_Aia0_t;
  double * c1_Bib0_t;
  double * c1_beta1_t;
  double * c1_Cic0_t;
  c1_threshold(chartInstance);
  c1_alpha1 = 1.0;
  c1_beta1 = 0.0;
  c1_TRANSB = 'N';
  c1_TRANSA = 'N';
  c1_m_t = (ptrdiff_t)(19);
  c1_n_t = (ptrdiff_t)(19);
  c1_k_t = (ptrdiff_t)(6);
  c1_lda_t = (ptrdiff_t)(19);
  c1_ldb_t = (ptrdiff_t)(6);
  c1_ldc_t = (ptrdiff_t)(19);
  c1_alpha1_t = (double *)(&c1_alpha1);
  c1_Aia0_t = (double *)(&c1_A[0]);
  c1_Bib0_t = (double *)(&c1_B[0]);
  c1_beta1_t = (double *)(&c1_beta1);
  c1_Cic0_t = (double *)(&c1_C[0]);
  dgemm(&c1_TRANSA, &c1_TRANSB, &c1_m_t, &c1_n_t, &c1_k_t, c1_alpha1_t,
        c1_Aia0_t, &c1_lda_t, c1_Bib0_t, &c1_ldb_t, c1_beta1_t, c1_Cic0_t,
        &c1_ldc_t);
}

static void init_dsm_address_info
  (SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c1_aircraftControl_smallerStateEKF_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2928630352U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(933636893U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4103154485U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2406932823U);
}

mxArray *sf_c1_aircraftControl_smallerStateEKF_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("eglVix3KmMLkw4zc7XSQ9C");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,7,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(19);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(19);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_aircraftControl_smallerStateEKF_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c1_aircraftControl_smallerStateEKF_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c1_aircraftControl_smallerStateEKF
  (void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[14],T\"S_OUT\",},{M[1],M[10],T\"cov_OUT\",},{M[1],M[13],T\"nu\",},{M[1],M[5],T\"states_OUT\",},{M[4],M[0],T\"cov\",S'l','i','p'{{M1x2[108 111],M[1],T\"C:\\Users\\Rudaba\\Documents\\PHD TAKE 2\\Simulations\\AircraftModelling\\simulateEKF_smallerStateVec.m\"}}},{M[4],M[0],T\"prev_p\",S'l','i','p'{{M1x2[112 118],M[1],T\"C:\\Users\\Rudaba\\Documents\\PHD TAKE 2\\Simulations\\AircraftModelling\\simulateEKF_smallerStateVec.m\"}}},{M[4],M[0],T\"prev_q\",S'l','i','p'{{M1x2[119 125],M[1],T\"C:\\Users\\Rudaba\\Documents\\PHD TAKE 2\\Simulations\\AircraftModelling\\simulateEKF_smallerStateVec.m\"}}},{M[4],M[0],T\"prev_r\",S'l','i','p'{{M1x2[126 132],M[1],T\"C:\\Users\\Rudaba\\Documents\\PHD TAKE 2\\Simulations\\AircraftModelling\\simulateEKF_smallerStateVec.m\"}}},{M[4],M[0],T\"states\",S'l','i','p'{{M1x2[101 107],M[1],T\"C:\\Users\\Rudaba\\Documents\\PHD TAKE 2\\Simulations\\AircraftModelling\\simulateEKF_smallerStateVec.m\"}}},{M[8],M[0],T\"is_active_c1_aircraftControl_smallerStateEKF\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 10, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_aircraftControl_smallerStateEKF_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _aircraftControl_smallerStateEKFMachineNumber_,
           1,
           1,
           1,
           0,
           11,
           0,
           0,
           0,
           0,
           1,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize ist own list of scripts */
        init_script_number_translation
          (_aircraftControl_smallerStateEKFMachineNumber_,
           chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,
             _aircraftControl_smallerStateEKFMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _aircraftControl_smallerStateEKFMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"accelerations");
          _SFD_SET_DATA_PROPS(1,1,1,0,"omega");
          _SFD_SET_DATA_PROPS(2,1,1,0,"ALP");
          _SFD_SET_DATA_PROPS(3,1,1,0,"BET");
          _SFD_SET_DATA_PROPS(4,1,1,0,"u");
          _SFD_SET_DATA_PROPS(5,2,0,1,"states_OUT");
          _SFD_SET_DATA_PROPS(6,1,1,0,"Vt");
          _SFD_SET_DATA_PROPS(7,2,0,1,"cov_OUT");
          _SFD_SET_DATA_PROPS(8,1,1,0,"H");
          _SFD_SET_DATA_PROPS(9,2,0,1,"nu");
          _SFD_SET_DATA_PROPS(10,2,0,1,"S_OUT");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,196);
        _SFD_CV_INIT_SCRIPT(0,1,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"simulateEKF_smallerStateVec",0,-1,10547);
        _SFD_CV_INIT_SCRIPT_IF(0,0,153,171,-1,1446);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 19;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)
            c1_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 19;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)
            c1_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)
            c1_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)
            c1_sf_marshallIn);
        }

        {
          real_T *c1_ALP;
          real_T *c1_BET;
          real_T *c1_Vt;
          real_T *c1_H;
          real_T (*c1_accelerations)[3];
          real_T (*c1_omega)[3];
          real_T (*c1_u)[4];
          real_T (*c1_states_OUT)[19];
          real_T (*c1_cov_OUT)[19];
          real_T (*c1_nu)[6];
          real_T (*c1_S_OUT)[6];
          c1_S_OUT = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 4);
          c1_nu = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 3);
          c1_H = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
          c1_cov_OUT = (real_T (*)[19])ssGetOutputPortSignal(chartInstance->S, 2);
          c1_Vt = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
          c1_states_OUT = (real_T (*)[19])ssGetOutputPortSignal(chartInstance->S,
            1);
          c1_u = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 4);
          c1_BET = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c1_ALP = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c1_omega = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c1_accelerations = (real_T (*)[3])ssGetInputPortSignal
            (chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c1_accelerations);
          _SFD_SET_DATA_VALUE_PTR(1U, *c1_omega);
          _SFD_SET_DATA_VALUE_PTR(2U, c1_ALP);
          _SFD_SET_DATA_VALUE_PTR(3U, c1_BET);
          _SFD_SET_DATA_VALUE_PTR(4U, *c1_u);
          _SFD_SET_DATA_VALUE_PTR(5U, *c1_states_OUT);
          _SFD_SET_DATA_VALUE_PTR(6U, c1_Vt);
          _SFD_SET_DATA_VALUE_PTR(7U, *c1_cov_OUT);
          _SFD_SET_DATA_VALUE_PTR(8U, c1_H);
          _SFD_SET_DATA_VALUE_PTR(9U, *c1_nu);
          _SFD_SET_DATA_VALUE_PTR(10U, *c1_S_OUT);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _aircraftControl_smallerStateEKFMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "nXyGsNGhtvM5KxpuLb1ocH";
}

static void sf_opaque_initialize_c1_aircraftControl_smallerStateEKF(void
  *chartInstanceVar)
{
  chart_debug_initialization
    (((SFc1_aircraftControl_smallerStateEKFInstanceStruct*) chartInstanceVar)->S,
     0);
  initialize_params_c1_aircraftControl_smallerStateEKF
    ((SFc1_aircraftControl_smallerStateEKFInstanceStruct*) chartInstanceVar);
  initialize_c1_aircraftControl_smallerStateEKF
    ((SFc1_aircraftControl_smallerStateEKFInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_aircraftControl_smallerStateEKF(void
  *chartInstanceVar)
{
  enable_c1_aircraftControl_smallerStateEKF
    ((SFc1_aircraftControl_smallerStateEKFInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_aircraftControl_smallerStateEKF(void
  *chartInstanceVar)
{
  disable_c1_aircraftControl_smallerStateEKF
    ((SFc1_aircraftControl_smallerStateEKFInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_aircraftControl_smallerStateEKF(void
  *chartInstanceVar)
{
  sf_gateway_c1_aircraftControl_smallerStateEKF
    ((SFc1_aircraftControl_smallerStateEKFInstanceStruct*) chartInstanceVar);
}

extern const mxArray*
  sf_internal_get_sim_state_c1_aircraftControl_smallerStateEKF(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_aircraftControl_smallerStateEKF
    ((SFc1_aircraftControl_smallerStateEKFInstanceStruct*)
     chartInfo->chartInstance);        /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_aircraftControl_smallerStateEKF();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c1_aircraftControl_smallerStateEKF
  (SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c1_aircraftControl_smallerStateEKF();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_aircraftControl_smallerStateEKF
    ((SFc1_aircraftControl_smallerStateEKFInstanceStruct*)
     chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_aircraftControl_smallerStateEKF
  (SimStruct* S)
{
  return sf_internal_get_sim_state_c1_aircraftControl_smallerStateEKF(S);
}

static void sf_opaque_set_sim_state_c1_aircraftControl_smallerStateEKF(SimStruct*
  S, const mxArray *st)
{
  sf_internal_set_sim_state_c1_aircraftControl_smallerStateEKF(S, st);
}

static void sf_opaque_terminate_c1_aircraftControl_smallerStateEKF(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_aircraftControl_smallerStateEKFInstanceStruct*)
                    chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_aircraftControl_smallerStateEKF_optimization_info();
    }

    finalize_c1_aircraftControl_smallerStateEKF
      ((SFc1_aircraftControl_smallerStateEKFInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_aircraftControl_smallerStateEKF
    ((SFc1_aircraftControl_smallerStateEKFInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_aircraftControl_smallerStateEKF(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c1_aircraftControl_smallerStateEKF
      ((SFc1_aircraftControl_smallerStateEKFInstanceStruct*)
       (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_aircraftControl_smallerStateEKF(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_aircraftControl_smallerStateEKF_optimization_info
      ();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,1,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,7);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 7; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3586096850U));
  ssSetChecksum1(S,(1911403802U));
  ssSetChecksum2(S,(2876918626U));
  ssSetChecksum3(S,(3920584750U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_aircraftControl_smallerStateEKF(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_aircraftControl_smallerStateEKF(SimStruct *S)
{
  SFc1_aircraftControl_smallerStateEKFInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc1_aircraftControl_smallerStateEKFInstanceStruct *)utMalloc
    (sizeof(SFc1_aircraftControl_smallerStateEKFInstanceStruct));
  memset(chartInstance, 0, sizeof
         (SFc1_aircraftControl_smallerStateEKFInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c1_aircraftControl_smallerStateEKF;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c1_aircraftControl_smallerStateEKF;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c1_aircraftControl_smallerStateEKF;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c1_aircraftControl_smallerStateEKF;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c1_aircraftControl_smallerStateEKF;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c1_aircraftControl_smallerStateEKF;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c1_aircraftControl_smallerStateEKF;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_aircraftControl_smallerStateEKF;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_aircraftControl_smallerStateEKF;
  chartInstance->chartInfo.mdlStart =
    mdlStart_c1_aircraftControl_smallerStateEKF;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c1_aircraftControl_smallerStateEKF;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c1_aircraftControl_smallerStateEKF_method_dispatcher(SimStruct *S, int_T
  method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_aircraftControl_smallerStateEKF(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_aircraftControl_smallerStateEKF(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_aircraftControl_smallerStateEKF(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_aircraftControl_smallerStateEKF_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
