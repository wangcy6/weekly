package com.wcy.thread;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/**
 * ͨ������һ��������wait()+notify() ������ͨ��
 * wait()��notify()����Ҫ���ڵ���ʱ�߳��Ѿ�����˶����������˶������������ĵ�����Ҫ����synchronized������synchronized���С�
 * 
 * ��������̵߳�ʱ�� û������
 * ����߳�һ���ʱ�� �ͱ���Ҫ��notifyAll()
 * 
 * @author leo-zeng
 */
public class NumberHolder
{

	private int number;

	public synchronized void increase()
	{
		while (number != 0)
		{
			try
			{
				//����nuber ��Ϊ0 ʱ �ȴ�
				wait();
			} catch (InterruptedException e)
			{
				e.printStackTrace();
			}
		}
		//��ִ�е����˵�� �Ѿ���������,����Ϊ0
		number++;
		System.out.println("��Ҫ����:" + number);
		//֪ͨ�ڵȴ����߳�
		notifyAll();
	}

	public synchronized void decrease()
	{
		while (number == 0)
		{
			try
			{
				//���ǵ������ʱ��  �ȴ�����
				wait();
			} catch (InterruptedException e)
			{
				e.printStackTrace();
			}
		}
		//��ִ�е����˵�� �Ѿ���������,���Ҳ�Ϊ0
		number--;
		System.out.println("��Ҫ�ݼ�:" + number);
		notifyAll();
	}

	public static void main(String[] args)
	{

		ExecutorService pool = Executors.newFixedThreadPool(10);

		NumberHolder holder = new NumberHolder();

		//ִ������
		pool.execute(new IncreaseThread(holder));
		pool.execute(new DecreaseThread(holder));

		//pool.execute(new IncreaseThread(holder));
		//pool.execute(new DecreaseThread(holder));

		pool.shutdown();
		try
		{
			pool.awaitTermination(300, TimeUnit.SECONDS);
		} catch (InterruptedException e)
		{
			e.printStackTrace();
		}
	}
}

/**
 * �ۼӵ���
 * 
 * @author leo
 */
class IncreaseThread extends Thread
{

	private NumberHolder numberHolder;

	public IncreaseThread(NumberHolder numberHolder)
	{
		this.numberHolder = numberHolder;
	}

	@Override
	public void run()
	{
		for (int i = 0; i < 20; i++)
		{
			//ÿ�ζ��в�����ӳ�
			try
			{
				Thread.sleep((long) Math.random() * 1000);
			} catch (InterruptedException e)
			{
				e.printStackTrace();
			}
			//ִ����������
			numberHolder.increase();
		}
	}
}

class DecreaseThread extends Thread
{

	private NumberHolder holder;

	public DecreaseThread(NumberHolder holder)
	{
		this.holder = holder;
	}

	@Override
	public void run()
	{
		for (int i = 0; i < 20; i++)
		{
			//ÿ�ζ��в�����ӳ�
			try
			{
				Thread.sleep((long) Math.random() * 1000);
			} catch (InterruptedException e)
			{
				e.printStackTrace();
			}
			//ִ�еݼ�����
			holder.decrease();
		}
	}
}
