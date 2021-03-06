//
//  PaymentMgr.cpp
//  SuperLife
//
//  Created by wang haibo on 15/1/29.
//
//

#include "PaymentMgr.h"
USING_NS_CC;
bool PaymentMgr::m_bPaying = false;
PaymentMgr* g_pPaymentMgrInstance = nullptr;
// 单体
PaymentMgr* PaymentMgr::getInstance()
{
    if( g_pPaymentMgrInstance == nullptr )
        g_pPaymentMgrInstance = new PaymentMgr();
    
    return g_pPaymentMgrInstance;
}
PaymentMgr::PaymentMgr()
:m_pPayResultListener(nullptr)
{
}
PaymentMgr::~PaymentMgr()
{
}
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
void PaymentMgr::setIAP(IOSIAP* iap)
{
    m_pIAP = iap;
#if COCOS2D_DEBUG
    [m_pIAP setDebug:true];
#endif
}
#endif
void PaymentMgr::payForProduct(TProductInfo info)
{
    if (m_bPaying)
    {
        CCLOG("Now is paying");
        return;
    }
    
    if (info.empty())
    {
        if (NULL != m_pPayResultListener)
        {
            onPayResult(kPayFail, "Product info error");
        }
        CCLOG("The product info is empty!");
        return;
    }
    else
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        if (m_pIAP != nil) {
            
            m_bPaying = true;
            m_currentInfo = info;
            
            NSMutableDictionary* dict = [NSMutableDictionary dictionary];
            std::map<std::string, std::string>::const_iterator it;
            for (it = info.begin(); it != info.end(); ++it)
            {
                NSString* pKey = [NSString stringWithUTF8String:it->first.c_str()];
                NSString* pValue = [NSString stringWithUTF8String:it->second.c_str()];
                [dict setValue:pValue forKey:pKey];
            }
            [m_pIAP payForProduct:dict];
        }
#endif
    }
}
void PaymentMgr::restorePurchase()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    if(m_pIAP != nil)
    {
        [m_pIAP restorePurchase];
    }
#endif
}
void PaymentMgr::onPayResult(PayResultCode ret, const char* msg)
{
    m_bPaying = false;
    if (m_pPayResultListener != nullptr)
        m_pPayResultListener->onPayResult(ret, msg, m_currentInfo);
    else
        CCLOG("Pay result listener is null!");
    
    m_currentInfo.clear();
    CCLOG("Pay result is : %d(%s)", (int) ret, msg);
}
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
void PaymentMgr::onRequestProductsResult(ProductsRequestResult ret, TProductList info, const char* msg)
{
    if(m_pPayResultListener != nullptr)
        m_pPayResultListener->onRequestProductsResult(ret, info);
    else
        CCLOG("Pay result listener is null!");
    if(ret == RequestSuccees)
        m_ProductList = info;
    CCLOG("request products result is : %d(%s)", (int) ret, msg);
}
#endif
const TProductList& PaymentMgr::getProductList() const
{
    return m_ProductList;
}
void PaymentMgr::setPayResultListener(PayResultListener* listener)
{
    m_pPayResultListener = listener;
}