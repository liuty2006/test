#include <QCoreApplication>
//#include "../libs/tinyxml/tinyxml.h"
#include "tinyxml.h"
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    printf("hello");

    // 新建的xml文件名字
        string filename = "example.xml";

        //    新建一个xml文件
        // 定义一个TiXmlDocument类指针
        TiXmlDocument* pWriteDoc = new TiXmlDocument();

        // xml的声明(三个属性：版本，编码格式，独立文件声明)
        TiXmlDeclaration* pDeclare = new TiXmlDeclaration("1.0", "UTF-8", "yes");
        pWriteDoc->LinkEndChild(pDeclare);			// 连接到最后

        // 根节点
        TiXmlElement* pRootElement = new TiXmlElement("telephonebook");
        pWriteDoc->LinkEndChild(pRootElement);		// 把根节点连接到最后

        // 二级节点
        TiXmlElement* pPersonElement = new TiXmlElement("person");	//通讯录节点
        pRootElement->LinkEndChild(pPersonElement);	// 连接到根节点下

        // 三级节点
        TiXmlElement* pNameElement = new TiXmlElement("name");
        // 文本
        TiXmlText* nameContent = new TiXmlText("xiaoming");		// 通讯录名字
        pNameElement->LinkEndChild(nameContent);	// 给三级节点添加文本
        pPersonElement->LinkEndChild(pNameElement);	// 把三级节点连接到二级节点下

        // 三级节点
        TiXmlElement* pAddrElement = new TiXmlElement("addr");	// 通讯录地址
        // 设置属性
        pAddrElement->SetAttribute("addr1","hubei");
        pAddrElement->SetAttribute("addr2","wuhan");
        pPersonElement->LinkEndChild(pAddrElement);	// 把三级节点连接到二级节点下

        // 三级节点
        TiXmlElement* pEmailElement = new TiXmlElement("email");// 通讯录邮件
        // 文本
        TiXmlText* emailContent = new TiXmlText("1234567@qq.com");
        pEmailElement->LinkEndChild(emailContent);	// 给三级节点添加文本
        pPersonElement->LinkEndChild(pEmailElement);// 把三级节点连接到二级节点下

        ///		保存到文件
        pWriteDoc->SaveFile(filename.c_str());
        printf( "new xml success, file's name is %s\n\n", filename.c_str());

         //   从文件中读取

        // 定义一个TiXmlDocument类指针
        TiXmlDocument* pReadDocument = new TiXmlDocument();

        // 读取文件
        if (!pReadDocument->LoadFile(filename.c_str()))
        {
            printf( "Could not load example xml file %s. Error='%s'\n", filename.c_str(),pReadDocument->ErrorDesc() );
            return 0;
        }

        printf("read xml file success, file' name is %s \n\n",filename.c_str());

        //读取文档声明信息(第一个子节点转换得到文档声明)
        TiXmlDeclaration* pDeclar = pReadDocument->FirstChild()->ToDeclaration();
        if (pDeclar != NULL)
        {
            printf("read declare, version is %s , encoding is %s\n",pDeclar->Version(), pDeclar->Encoding());
        }

        // 得到文件根节点
        pRootElement = pReadDocument->RootElement();

        //    遍历元素，打印

        printf("begin read all xml element \n\n");

        // 遍历所有的person
        // 函数FirstChildElement()		:	找到指定名字的元素
        // 函数NextSiblingElement		:	在同一级元素中查找下一个指定名字的元素
        int i = 0;
        for (TiXmlElement* pItem = pRootElement->FirstChildElement("person"); pItem; pItem = pItem->NextSiblingElement("person"))
        {
            printf("read the %d person \n",++i);

            // 名字
            TiXmlElement* pName = pItem->FirstChildElement("name");
            if (pName != NULL)
            {
                printf("the %d person's name = %s \n", i, pName->GetText());
            }

            // 地址
            TiXmlElement* pAddr = pItem->FirstChildElement("addr");
            if (pAddr != NULL)
            {
                // 第一个属性
                TiXmlAttribute* pAddr1 = pAddr->FirstAttribute();
                if (pAddr1 != NULL)
                {
                    printf("the %d person's addr1 = %s \n", i, pAddr1->Value());

                    // 下一个属性
                    TiXmlAttribute* pAddr2 = pAddr1->Next();
                    if (pAddr2 != NULL)
                    {
                        printf("the %d person's addr2 = %s \n", i, pAddr2->Value());
                    }
                }
            }

            printf("\n\n");
        }

        //    删除元素，属性

        TiXmlElement* pPerson = pRootElement->FirstChildElement("person");
        if (pPerson != NULL)
        {
            // 这里演示删除"email"元素，删除其他节点也是一样的办法
            TiXmlElement* pEmail = pPerson->FirstChildElement("email");
            if (pEmail != NULL)
            {
                pPerson->RemoveChild(pEmail);
            }

            // 这里演示修改"addr"元素
            TiXmlElement* pAddr = pPerson->FirstChildElement("addr");
            if (pAddr != NULL)
            {
                pAddr->SetAttribute("addr2", "huanggang");	// 修改属性值

                // 删除属性
                //pAddr->RemoveAttribute("addr1");
            }
        }

        //	增加元素

        // 新建一个元素，名字：person
        TiXmlElement* pNewElement = new TiXmlElement("person");

        // 给新建的元素创建子元素并连接到最后
        TiXmlElement* pNameElementAdd = new TiXmlElement("name");		// 元素：name
        TiXmlText* pNameText = new TiXmlText("zhangsan");
        pNameElementAdd->LinkEndChild(pNameText);						// 该元素下添加文本内容

        TiXmlElement* pAddrElementAdd = new TiXmlElement("addr");		// 元素：addr
        pAddrElementAdd->SetAttribute("addr1","guangdong");
        pAddrElementAdd->SetAttribute("addr2","shenzhen");				// 该元素下添加属性


        TiXmlElement* pEmailElementAdd = new TiXmlElement("email");	// 元素：email
        TiXmlText* pEmailText = new TiXmlText("zhangsan@qq.com");
        pEmailElementAdd->LinkEndChild(pEmailText);					// 该元素下添加文本内容

        // 都挂接到新建元素下
        pNewElement->LinkEndChild(pNameElementAdd);
        pNewElement->LinkEndChild(pAddrElementAdd);
        pNewElement->LinkEndChild(pEmailElementAdd);

        // 把这个新建元素挂在根节点最后
        pRootElement->LinkEndChild(pNewElement);

        printf("add new element success\n");

        ///	再次保存到文件
        if (pReadDocument->SaveFile(filename.c_str()))
        {
            printf("save file success\n");
        }

        getchar();

    return a.exec();
}
