package com.job.lock;

import java.util.HashMap;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;


public class CachedTest
{
    volatile HashMap<String,String> cacheMap = new HashMap<String,String>();
    
    ReadWriteLock rwLock = new ReentrantReadWriteLock();
    
    public String getS(String key)
    {
        rwLock.readLock().lock();
        String value = null;
        try
        {
            if(cacheMap.get(key) == null)
            {
                rwLock.readLock().unlock();
                rwLock.writeLock().lock();
                try
                {
                    //������Ҫ�ٴ��жϣ���ֹ�����������߳��ٴη�������
                    if(cacheMap.get(key) == null)
                    {
                        value = "" + Thread.currentThread().getName();
                        cacheMap.put(key, value);
                        System.out.println(Thread.currentThread().getName() + "put the value" + value);
                    }
                }
                finally
                {
                    //�������������������Ļ�ȡ��д�����ͷ�˳���ܵߵ�
                    rwLock.readLock().lock();
                    rwLock.writeLock().unlock();
                }
            }
        }
        finally
        {
            rwLock.readLock().unlock();
        }
        return cacheMap.get(key);
    }
}