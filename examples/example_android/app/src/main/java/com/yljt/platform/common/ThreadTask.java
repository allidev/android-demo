package com.yljt.platform.common;


import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.support.annotation.MainThread;
import android.support.annotation.WorkerThread;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * Created by LILIN on 2016/12/27.
 */

public abstract class ThreadTask<T>  {

    private static Handler handler ;

    /**
     * 线程池，创建一个定长线程池，可控制线程最大并发数，超出的线程会在队列中等待。
     */
    private static ExecutorService executorService = Executors.newFixedThreadPool( 15 ) ;

    public ThreadTask(){

    }

    private void run() {
        executorService.execute(new Runnable() {
            @Override
            public void run() {
                Message message = Message.obtain() ;
                message.obj = new ResultData<T>( ThreadTask.this , onDoInBackground()) ;
                getHandler().sendMessage( message ) ;
            }
        });
    }

    /**
     * 任务开始之前调用，运行在主线程
     */
    @MainThread
    public void onStart(){ }

    /**
     * 子线程中调用，运行在子线程
     * @return
     */
    @WorkerThread
    public abstract T onDoInBackground() ;

    /**
     * 子线程返回的结果，运行在主线程
     * @param t
     */
    @MainThread
    public void onResult( T t ){ }


    /**
     * 开始执行
     */
    public void execute(){
        onStart();
        run();
    }

    /**
     * 单例模式，保证handler只有一个实例
     * @return
     */
    private static Handler getHandler(){
        if ( handler == null ){
            synchronized ( MHandler.class ){
                if ( handler == null ){
                    handler= new MHandler( Looper.getMainLooper()) ;
                }
            }
        }
        return handler ;
    }

    private static class MHandler extends Handler {

        public MHandler( Looper looper ){
            super( looper );
        }

        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            //在这里接收子线程发过来的消息
            ResultData resultData = (ResultData) msg.obj;
            resultData.threadTask.onResult( resultData.data );
        }
    }

    /**
     * handler发送数据的实体
     * @param <Data>
     */
    private static class ResultData<Data>{
        ThreadTask threadTask ;
        Data data ;
        public ResultData( ThreadTask threadTask  ,Data data  ){
            this.threadTask = threadTask ;
            this.data = data ;
        }
    }
}
