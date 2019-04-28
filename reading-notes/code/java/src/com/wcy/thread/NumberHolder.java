package com.wcy.thread;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/**
 * 通过共享一个变量，wait()+notify() 来践行通信
 * wait()和notify()方法要求在调用时线程已经获得了对象的锁，因此对这两个方法的调用需要放在synchronized方法或synchronized块中。
 * 
 * 针对两个线程的时候 没有问题
 * 针对线程一多的时候， 就必须要用notifyAll()
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
				//若是nuber 不为0 时 等待
				wait();
			} catch (InterruptedException e)
			{
				e.printStackTrace();
			}
		}
		//能执行到这里，说明 已经被唤醒了,并且为0
		number++;
		System.out.println("我要递增:" + number);
		//通知在等待的线程
		notifyAll();
	}

	public synchronized void decrease()
	{
		while (number == 0)
		{
			try
			{
				//若是等于零的时候  等待唤醒
				wait();
			} catch (InterruptedException e)
			{
				e.printStackTrace();
			}
		}
		//能执行到这里，说明 已经被唤醒了,并且不为0
		number--;
		System.out.println("我要递减:" + number);
		notifyAll();
	}

	public static void main(String[] args)
	{

		ExecutorService pool = Executors.newFixedThreadPool(10);

		NumberHolder holder = new NumberHolder();

		//执行任务
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
 * 累加的类
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
			//每次都有不多的延迟
			try
			{
				Thread.sleep((long) Math.random() * 1000);
			} catch (InterruptedException e)
			{
				e.printStackTrace();
			}
			//执行新增操作
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
			//每次都有不多的延迟
			try
			{
				Thread.sleep((long) Math.random() * 1000);
			} catch (InterruptedException e)
			{
				e.printStackTrace();
			}
			//执行递减函数
			holder.decrease();
		}
	}
}
