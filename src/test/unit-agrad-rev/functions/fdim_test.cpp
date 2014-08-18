#include <stan/agrad/rev/functions/fdim.hpp>
#include <test/unit/agrad/util.hpp>
#include <gtest/gtest.h>
#include <stan/agrad/rev.hpp>
#include <stan/math/functions/fdim.hpp>

TEST(AgradRev,fdim_vv) {
  AVAR a = 3.0;
  AVAR b = 4.0;
  AVAR f = fdim(a,b);
  EXPECT_FLOAT_EQ(0.0,f.val());

  AVEC x = createAVEC(a,b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
  EXPECT_FLOAT_EQ(0.0,grad_f[1]);

  a = std::numeric_limits<AVAR>::infinity();
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(a,a).val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::fdim(a,b).val());
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(b,a).val());
}  
TEST(AgradRev,fdim_vv_2) {
  AVAR a = 7.0;
  AVAR b = 2.0;
  AVAR f = fdim(a,b);
  EXPECT_FLOAT_EQ(5.0,f.val());

  AVEC x = createAVEC(a,b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0,grad_f[0]);
  EXPECT_FLOAT_EQ(-1.0,grad_f[1]);

  a = std::numeric_limits<AVAR>::infinity();
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(a,a).val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::fdim(a,b).val());
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(b,a).val());
}  
TEST(AgradRev,fdim_vd) {
  AVAR a = 3.0;
  double b = 4.0;
  AVAR f = fdim(a,b);
  EXPECT_FLOAT_EQ(0.0,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);

  AVAR infinityavar = std::numeric_limits<AVAR>::infinity();
  double infinitydouble = std::numeric_limits<double>::infinity();
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(infinityavar,infinitydouble).val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::fdim(infinityavar,b).val());
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(a,infinitydouble).val());
}  

TEST(AgradRev,fdim_vd_2) {
  AVAR a = 7.0;
  double b = 2.0;
  AVAR f = fdim(a,b);
  EXPECT_FLOAT_EQ(5.0,f.val());

  AVEC x = createAVEC(a);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(1.0,grad_f[0]);

  AVAR infinityavar = std::numeric_limits<AVAR>::infinity();
  double infinitydouble = std::numeric_limits<double>::infinity();
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(infinityavar,infinitydouble).val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::fdim(infinityavar,b).val());
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(a,infinitydouble).val());
}  
TEST(AgradRev,fdim_dv) {
  double a = 3.0;
  AVAR b = 4.0;
  AVAR f = fdim(a,b);
  EXPECT_FLOAT_EQ(0.0,f.val());

  AVEC x = createAVEC(b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(0.0,grad_f[0]);
 
  AVAR infinityavar = std::numeric_limits<AVAR>::infinity();
  double infinitydouble = std::numeric_limits<double>::infinity();
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(infinitydouble,infinityavar).val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::fdim(infinitydouble,b).val());
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(a,infinityavar).val());
}
TEST(AgradRev,fdim_dv_2) {
  double a = 7.0;
  AVAR b = 2.0;
  AVAR f = fdim(a,b);
  EXPECT_FLOAT_EQ(5.0,f.val());

  AVEC x = createAVEC(b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(-1.0,grad_f[0]);

  AVAR infinityavar = std::numeric_limits<AVAR>::infinity();
  double infinitydouble = std::numeric_limits<double>::infinity();
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(infinitydouble,infinityavar).val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::fdim(infinitydouble,b).val());
  EXPECT_FLOAT_EQ(0.0, stan::math::fdim(a,infinityavar).val());
}  

TEST(AgradRev, fdim_nan) {
  double nan = std::numeric_limits<double>::quiet_NaN();
  stan::agrad::var nan_v = std::numeric_limits<double>::quiet_NaN();
  double a = 3.0;
  stan::agrad::var a_v = 3.0;

  EXPECT_PRED1(boost::math::isnan<double>,
               stan::agrad::fdim(a_v, nan_v).val());
  EXPECT_PRED1(boost::math::isnan<double>,
               stan::agrad::fdim(a, nan_v).val());
  EXPECT_PRED1(boost::math::isnan<double>,
               stan::agrad::fdim(a_v, nan).val());
  EXPECT_PRED1(boost::math::isnan<double>,
               stan::agrad::fdim(nan_v, a).val());
  EXPECT_PRED1(boost::math::isnan<double>,
               stan::agrad::fdim(nan, a_v).val());
  EXPECT_PRED1(boost::math::isnan<double>,
               stan::agrad::fdim(nan_v, a_v).val());
  EXPECT_PRED1(boost::math::isnan<double>,
               stan::agrad::fdim(nan_v, nan_v).val());
  EXPECT_PRED1(boost::math::isnan<double>,
               stan::agrad::fdim(nan_v, nan).val());
  EXPECT_PRED1(boost::math::isnan<double>,
               stan::agrad::fdim(nan, nan_v).val());

}
