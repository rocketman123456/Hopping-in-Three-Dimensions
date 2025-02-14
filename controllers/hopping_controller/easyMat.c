/**********************************************************
**             Email:@qq.com   QQ:1069841355
**---------------------------------------------------------
**  Description: 此文件为一个简单的矩阵运算库文件, 处理过程中不提示报错信息
**  Version    :
**  Notes      :
**  Author     : 于宪元
**********************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#include "easyMat.h"

//-----------------------------------------------------------function
/*
创建矩阵
*/
void easyMat_create(matTypeDef *mat, uint16_t row, uint16_t col)
{
    mat->row = row;
    mat->col = col;
    mat->data = (double **)malloc(row * sizeof(double *)); //指针的指针
    for (int i = 0; i < row; i++)
    {
        mat->data[i] = (double *)malloc(col * sizeof(double)); //每行数据的指针
    }
}
/*
释放矩阵内存
*/
void easyMat_free(matTypeDef *mat)
{
    for (uint16_t i = 0; i < mat->row; i++)
    {
        free(mat->data[i]);
    }
    free(mat->data);
}
/*
初始化矩阵
*/
void easyMat_init(matTypeDef *mat, double *data)
{
    for (uint16_t i = 0; i < mat->row; i++)
    {
        for (uint16_t j = 0; j < mat->col; j++)
        {
            mat->data[i][j] = data[i * mat->col + j];
        }
    }
}
/*
所有元素清零
*/
void easyMat_clear(matTypeDef *mat)
{
    for (uint16_t i = 0; i < mat->row; i++)
    {
        for (uint16_t j = 0; j < mat->col; j++)
        {
            mat->data[i][j] = 0;
        }
    }
}
/*
将方阵初始化为单位阵
*/
void easyMat_eye(matTypeDef *mat)
{
    for (uint16_t i = 0; i < mat->row; i++)
    {
        for (uint16_t j = 0; j < mat->col; j++)
        {
            if (i == j)
                mat->data[i][j] = 1;
            else
                mat->data[i][j] = 0;
        }
    }
}
/*
矩阵加法
outMat = mat1 + mat2
*/
void easyMat_add(matTypeDef *outMat, matTypeDef *mat1, matTypeDef *mat2)
{
    for (uint16_t i = 0; i < outMat->row; i++)
    {
        for (uint16_t j = 0; j < outMat->col; j++)
        {
            outMat->data[i][j] = mat1->data[i][j] + mat2->data[i][j];
        }
    }
}
/*
矩阵减法
outMat = mat1 - mat2
*/
void easyMat_sub(matTypeDef *outMat, matTypeDef *mat1, matTypeDef *mat2)
{
    for (uint16_t i = 0; i < outMat->row; i++)
    {
        for (uint16_t j = 0; j < outMat->col; j++)
        {
            outMat->data[i][j] = mat1->data[i][j] - mat2->data[i][j];
        }
    }
}
/*
矩阵乘法
outMat = mat1 * mat2
*/
void easyMat_mult(matTypeDef *outMat, matTypeDef *mat1, matTypeDef *mat2)
{
    for (uint16_t i = 0; i < mat1->row; i++)
    {
        for (uint16_t j = 0; j < mat2->col; j++)
        {
            outMat->data[i][j] = 0;
            for (uint16_t m = 0; m < mat1->col; m++)
            {
                outMat->data[i][j] += mat1->data[i][m] * mat2->data[m][j];
            }
        }
    }
}
/*
矩阵转置
dstMat = srcMat'
*/
void easyMat_trans(matTypeDef *dstMat, matTypeDef *srcMat)
{
    for (uint16_t i = 0; i < dstMat->row; i++)
    {
        for (uint16_t j = 0; j < dstMat->col; j++)
        {
            dstMat->data[i][j] = srcMat->data[j][i];
        }
    }
}
/*
矩阵复制
dstMat = srcMat
*/
void easyMat_copy(matTypeDef *dstMat, matTypeDef *srcMat)
{
    for (uint16_t i = 0; i < dstMat->row; i++)
    {
        for (uint16_t j = 0; j < dstMat->col; j++)
        {
            dstMat->data[i][j] = srcMat->data[i][j];
        }
    }
}
/*
绕X轴旋转的3*3旋转矩阵方阵
Mat = RotX(angle)
采用角度制
*/
void easyMat_rotX(matTypeDef *Mat, double angle)
{
    //转成弧度制
    double a = angle * 3.141592654f / 180.0f;
    //初始化旋转矩阵
    double RotX_InitPdata[9] = {
        1.0f, 0.0f, 0.0f,
        0.0f, cosf(a), -sinf(a),
        0.0f, sinf(a), cosf(a)};
    easyMat_init(Mat, RotX_InitPdata);
}
/*
绕Y轴旋转的3*3旋转矩阵方阵
Mat = RotY(angle)
采用角度制
*/
void easyMat_rotY(matTypeDef *Mat, double angle)
{
    //转成弧度制
    double a = angle * 3.141592654f / 180.0f;
    //初始化旋转矩阵
    double RotY_InitPdata[9] = {
        cosf(a), 0.0f, sinf(a),
        0.0f, 1.0f, 0.0f,
        -sinf(a), 0.0f, cosf(a)};
    easyMat_init(Mat, RotY_InitPdata);
}
/*
绕Z轴旋转的3*3旋转矩阵方阵
Mat = RotZ(angle)
采用角度制
*/
void easyMat_rotZ(matTypeDef *Mat, double angle)
{
    //转成弧度制
    double a = angle * 3.141592654f / 180.0f;
    //初始化旋转矩阵
    double RotZ_InitPdata[9] = {
        cosf(a), -sinf(a), 0.0f,
        sinf(a), cosf(a), 0.0f,
        0.0f, 0.0f, 1.0f};
    easyMat_init(Mat, RotZ_InitPdata);
}

/*
求复合旋转矩阵
outRot=RotY(yaw)*RotZ(pitch)*RotX(roll);
*/
void easyMat_RPY(matTypeDef *outRot, double roll, double pitch, double yaw)
{
    matTypeDef RotX, RotY, RotZ, temp;

    easyMat_create(&RotX, 3, 3);
    easyMat_create(&RotY, 3, 3);
    easyMat_create(&RotZ, 3, 3);
    easyMat_create(&temp, 3, 3);

    easyMat_rotX(&RotX, roll);
    easyMat_rotY(&RotY, pitch);
    easyMat_rotZ(&RotZ, yaw);

    //easyMat_mult(&temp, &RotY, &RotZ);
    //easyMat_mult(outRot, &RotX, &temp);
    //easyMat_mult(&temp, &RotY, &RotZ);
    easyMat_mult(&temp, &RotZ, &RotY);
    easyMat_mult(outRot, &temp, &RotX);

    easyMat_free(&RotX);
    easyMat_free(&RotY);
    easyMat_free(&RotZ);
    easyMat_free(&temp);
}
/*
矩阵求逆
dstMat = srcMat^(-1)
*/
void easyMat_inv(matTypeDef *dstMat, matTypeDef *srcMat)
{
    // code
}
