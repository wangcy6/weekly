package com.job.stl;

import java.util.HashMap;
import java.util.Map;

public class MapTest {
	
	public void mapTest(){
		//HashMap的key 可以同时为空, 重复
	    Map<Object,Object> map = new HashMap<Object,Object>();
	    map.put(null,1);
	    map.put(null,2);
	    map.put(1,1);
	    //map.put(null,null);
	    for (Object obj : map.keySet()){
	        System.out.println("key="+obj +" value="+map.get(obj));
	    }
	    System.out.println(map);
	    System.out.println(map.get(null));
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		MapTest mt =new MapTest();
		mt.mapTest();
	}

}
