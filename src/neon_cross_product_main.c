#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "android_arm_util.h"
#include "neon_cross_product.h"

int main(int argc, char* argv[])
{
    FUNC_ENTRANCE_LOG;
    float a_vector[3] = {-10.0f, 12.1f,  2.0f};
    float b_vector[3] = {  0.5f,102.3f, -7.9f};
    float vec_a_4[12] = {  2.4f,  30.6f,  -4.3f,                     // a_{1,i}, a_{1,j}, a_{1,k}
                         121.1f,  -0.9f,  32.5f,                     // a_{2,i}, a_{2,j}, a_{2,k}
                          23.2f,  13.3f,   0.7f,                     // a_{3,i}, a_{3,j}, a_{3,k}
                           2.1f,   4.3f,   2.3f};                    // a_{4,i}, a_{4,j}, a_{4,k}
    float vec_b_4[12] = {-23.2f,  -3.2f,   1.2f,                     // b_{1,i}, b_{1,j}, b_{1,k}
                          23.4f,  23.2f,  21.1f,                     // b_{2,i}, b_{2,j}, b_{2,k}
                           2.3f,   1.2f,  -0.1f,                     // b_{3,i}, b_{3,j}, b_{3,k}
                           0.1f,  -0.9f, 100.3f};                    // b_{4,i}, b_{4,j}, b_{4,k}
    c_cross_product(a_vector, b_vector);
    neon_cross_product1(a_vector, b_vector);
    neon_cross_product2(a_vector, b_vector);

    ex_log(LOG_DEBUG, "%s cross product of vec_a_4 1", __func__);
    printf("\n%s cross product of vec_a_4 1\n", __func__);
    c_cross_product(vec_a_4, vec_b_4);
    neon_cross_product1(vec_a_4, vec_b_4);
    neon_cross_product2(vec_a_4, vec_b_4);

    ex_log(LOG_DEBUG, "%s cross product of vec_a_4 2", __func__);
    printf("\n%s cross product of vec_a_4 2\n", __func__);
    c_cross_product(vec_a_4+3, vec_b_4+3);
    neon_cross_product1(vec_a_4+3, vec_b_4+3);
    neon_cross_product2(vec_a_4+3, vec_b_4+3);

    ex_log(LOG_DEBUG, "%s cross product of vec_a_4 3", __func__);
    printf("\n%s cross product of vec_a_4 3\n", __func__);
    c_cross_product(vec_a_4+6, vec_b_4+6);
    neon_cross_product1(vec_a_4+6, vec_b_4+6);
    neon_cross_product2(vec_a_4+6, vec_b_4+6);

    ex_log(LOG_DEBUG, "%s cross product of vec_a_4 4", __func__);
    printf("\n%s cross product of vec_a_4 4\n", __func__);
    c_cross_product(vec_a_4+9, vec_b_4+9);
    neon_cross_product1(vec_a_4+9, vec_b_4+9);
    neon_cross_product2(vec_a_4+9, vec_b_4+9);

    ex_log(LOG_DEBUG, "%s cross product of vec_a_4 by neon_cross_product_4_vec", __func__);
    printf("%s cross product of vec_a_4 by neon_cross_product_4_vec\n", __func__);
    neon_cross_product_4_vec(vec_a_4, vec_b_4);


    FUNC_EXIT_LOG;
    return 0;
}
