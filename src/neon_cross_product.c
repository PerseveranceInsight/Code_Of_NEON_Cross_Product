#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <arm_neon.h> 

#include "neon_cross_product.h"
#include "android_arm_util.h"

void c_cross_product(const float *vec_a, const float *vec_b)
{
    FUNC_ENTRANCE_LOG;
    int i = 0;
    float ret_a = 0.0f, ret_b = 0.0f;
    float vec_aa[4] = {vec_a[1], vec_a[2], vec_a[0], vec_a[1]};
    float vec_bb[4] = {vec_b[1], vec_b[2], vec_b[0], vec_b[1]};
    float vec_res[3] = {0.0f};

    for (i = 0; i<3; i++)
    {
        ret_a = vec_aa[i]*vec_bb[i+1];
        ret_b = vec_bb[i]*vec_aa[i+1];
        vec_res[i] = ret_a - ret_b;
    }
    ex_log(LOG_DEBUG, "%s vec_res %f %f %f", __func__, vec_res[0], vec_res[1], vec_res[2]);
    printf("%s vec_res %f %f %f\n", __func__, vec_res[0], vec_res[1], vec_res[2]);
    FUNC_EXIT_LOG;
}

void neon_cross_product1(const float *vec_a, const float *vec_b)
{
    FUNC_ENTRANCE_LOG;
    float vec_aa[5] = {vec_a[1], vec_a[2], vec_a[0], vec_a[1], vec_a[2]};
    float vec_bb[5] = {vec_b[1], vec_b[2], vec_b[0], vec_b[1], vec_b[2]};
    float vec_rr[4] = {0.0f};
    float32x4_t vec_a1_neon, vec_a2_neon, vec_b1_neon, vec_b2_neon, vec_r;
    
    vec_r = vmovq_n_f32(0);
    vec_a1_neon = vld1q_f32(vec_aa);
    vec_a2_neon = vld1q_f32(vec_aa+1);
    vec_b1_neon = vld1q_f32(vec_bb);
    vec_b2_neon = vld1q_f32(vec_bb+1);

    vec_r = vmulq_f32(vec_a1_neon, vec_b2_neon);
    vec_r = vmlsq_f32(vec_r, vec_a2_neon, vec_b1_neon);
    vst1q_f32(vec_rr, vec_r);
    ex_log(LOG_DEBUG, "%s vec_r %f %f %f", __func__, vec_rr[0], vec_rr[1], vec_rr[2]);
    printf("%s vec_r %f %f %f\n", __func__, vec_rr[0], vec_rr[1], vec_rr[2]);
    FUNC_EXIT_LOG;
}

void neon_cross_product2(const float *vec_a, const float *vec_b)
{
    FUNC_ENTRANCE_LOG;
    float vec_r[3] = {0.0f};
    float32x2_t vec_neon_a1 = vld1_f32((float*)vec_a+1);                         // a_[k], a_[j]
    float32x2_t vec_neon_a2 = vld1_f32((float*)vec_a);                           // a_[j], a_[k]
    float32x2_t vec_neon_b1 = vld1_f32((float*)vec_b+1);                         // b_[k], b_[j]
    float32x2_t vec_neon_b2 = vld1_f32((float*)vec_b);                           // b_[j], b-[k]

    float32x4_t vec_neon_a = vcombine_f32(vec_neon_a1, vec_neon_a2);             // Q register = [a_[j], a_[i], a_[k], a_[j]]
    float32x4_t vec_neon_b = vcombine_f32(vec_neon_b1, vec_neon_b2);             // Q register = [b_[j], b_[i], b_[k], b_[j]]
    float32x4_t vec_neon_a_rot = vextq_f32(vec_neon_a, vec_neon_a, 1);           // Q register = [a_[j], a_[j], a_[i], a_[k]]
    float32x4_t vec_neon_b_rot = vextq_f32(vec_neon_b, vec_neon_b, 1);           // Q regsiter = [b_[j], b_[j], b_[i], b_[k]]
    float32x4_t prod_res_neon = vmulq_f32(vec_neon_a, vec_neon_b_rot);
    prod_res_neon = vmlsq_f32(prod_res_neon, vec_neon_a_rot, vec_neon_b);
    vst1_f32(vec_r, vget_low_f32(prod_res_neon));
    vst1_lane_f32(vec_r+2, vget_high_f32(prod_res_neon), 0);
    ex_log(LOG_DEBUG, "%s vec_r %f %f %f", __func__, vec_r[0], vec_r[1], vec_r[2]);
    printf("%s vec_r %f %f %f\n", __func__, vec_r[0], vec_r[1], vec_r[2]);

    FUNC_EXIT_LOG;
}

void neon_cross_product_4_vec(const float *vec_a4, const float *vec_b4)
{
    FUNC_ENTRANCE_LOG;
    float vec_r[12] = {0};
                                                               // 
    float32x4x3_t neon_4_vec_a = vld3q_f32((float*)vec_a4);    // a_{4,k}, a_{3,k}, a_{2,k}, a_{1,k}, a_{4,j}, a_{3,j}, a_{2,j}, a_{1,j}, a_{4,i}, a_{3,i}, a_{2,i}, a_{1,i}
    float32x4x3_t neon_4_vec_b = vld3q_f32((float*)vec_b4);    // b_{4,k}, b_{3,k}, b_{2,k}, b_{1,k}, b_{4,j}, b_{3,j}, b_{2,j}, b_{1,j}, b_{4,i}, b_{3,i}, b_{2,i}, b_{1,i}
    float32x4x3_t neon_4_vec_r;

    neon_4_vec_r.val[0] = vmulq_f32(neon_4_vec_a.val[1], neon_4_vec_b.val[2]);
    neon_4_vec_r.val[0] = vmlsq_f32(neon_4_vec_r.val[0], neon_4_vec_a.val[2], neon_4_vec_b.val[1]);

    neon_4_vec_r.val[1] = vmulq_f32(neon_4_vec_a.val[2], neon_4_vec_b.val[0]);
    neon_4_vec_r.val[1] = vmlsq_f32(neon_4_vec_r.val[1], neon_4_vec_a.val[0], neon_4_vec_b.val[2]);

    neon_4_vec_r.val[2] = vmulq_f32(neon_4_vec_a.val[1], neon_4_vec_b.val[0]);
    neon_4_vec_r.val[2] = vmlsq_f32(neon_4_vec_r.val[2], neon_4_vec_a.val[0], neon_4_vec_b.val[1]);
    vst3q_f32(vec_r, neon_4_vec_r);

    ex_log(LOG_DEBUG, "%s vec_r1 %f %f %f", __func__, vec_r[0], vec_r[1], vec_r[2]);
    ex_log(LOG_DEBUG, "%s vec_r2 %f %f %f", __func__, vec_r[3], vec_r[4], vec_r[5]);
    ex_log(LOG_DEBUG, "%s vec_r3 %f %f %f", __func__, vec_r[6], vec_r[7], vec_r[8]);
    ex_log(LOG_DEBUG, "%s vec_r4 %f %f %f", __func__, vec_r[9], vec_r[10], vec_r[11]);

    printf("%s vec_r1 %f %f %f\n", __func__, vec_r[0], vec_r[1], vec_r[2]);
    printf("%s vec_r2 %f %f %f\n", __func__, vec_r[3], vec_r[4], vec_r[5]);
    printf("%s vec_r3 %f %f %f\n", __func__, vec_r[6], vec_r[7], vec_r[8]);
    printf("%s vec_r4 %f %f %f\n", __func__, vec_r[9], vec_r[10], vec_r[11]);

    FUNC_EXIT_LOG;
}
