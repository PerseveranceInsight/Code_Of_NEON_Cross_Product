#ifndef __NEON_CROSS_PRODUCT_H__
#define __NEON_CROSS_PRODUCT_H__
void c_cross_product(const float *vec_a, const float *vec_b);
void neon_cross_product1(const float *vec_a, const float *vec_b);
void neon_cross_product2(const float *vec_a, const float *vec_b);
void neon_cross_product_4_vec(const float *vec_a4, const float *vec_b4);
#endif
