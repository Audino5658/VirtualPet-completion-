/*==============================================================================
            Copyright (c) 2010-2013 QUALCOMM Austria Research Center GmbH.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary
==============================================================================*/

package com.qualcomm.QCARSamples.MultiTargets;

import java.lang.ref.WeakReference;

import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.ImageButton;
import android.widget.Toast;

public class GUIManager {

    // Custom views:
    private View overlayView;
    private ImageButton foodbutton;
    private ImageButton shopbutton;
    private ImageButton battlebutton;
    private ImageButton advbutton;
    
    private ImageButton cheesebutton;
    private ImageButton berrybutton;
    
    private ImageButton shopclosebutton;
    private ImageButton shopskinbutton;
    private ImageButton shopfoodbutton;
    private ImageButton shoparmbutton;
    
    private ImageButton shopcatbutton;
    private ImageButton shopbearbutton;
    private ImageButton shoprabbitbutton;   
    private ImageButton skinUnknown1;
    private ImageButton skinUnknown2;
    private ImageButton skinUnknown3;
    private ImageButton skinUpbutton;
    private ImageButton skinDownbutton;
    
    private ImageButton shopberrybutton;
    private ImageButton shopcheesebutton;
    private ImageButton shopunknown1;
    private ImageButton shopunknown2;
    private ImageButton shopunknown3;
    private ImageButton shopunknown4;
    private ImageButton shopupbutton;
    private ImageButton shopdownbutton;
    
    private ImageButton armarrowbutton;
    private ImageButton armbullet1button;
    private ImageButton armbullet2button;
    private ImageButton armUnknown1;
    private ImageButton armUnknown2;
    private ImageButton armUnknown3;
    private ImageButton armUpButton;
    private ImageButton armDownButton;
    
    private ImageButton advshootbutton;
    private ImageButton advmoneybutton;
    private ImageButton advclosebutton;
    
    private ImageButton shotbutton;

    
    // A Handler for working with the GUI from other threads:
    static class MyActivityHandler extends Handler
    {
        private WeakReference<GUIManager> guiManager;
        private Context context;

        MyActivityHandler(GUIManager guim, Context c)
        {
            guiManager = new WeakReference<GUIManager>(guim);
            context = c;
        }

       public void handleMessage(Message msg)
        {
              ImageButton foodbutton       = guiManager.get().foodbutton;
              ImageButton shopbutton       = guiManager.get().shopbutton;
              ImageButton battlebutton     = guiManager.get().battlebutton;
    	      ImageButton advbutton        = guiManager.get().advbutton;
    	      
    	      ImageButton cheesebutton     = guiManager.get().cheesebutton;
    	      ImageButton berrybutton      = guiManager.get().berrybutton;
    	      
    	      ImageButton shopclosebutton  = guiManager.get().shopclosebutton;
    	      ImageButton shopskinbutton   = guiManager.get().shopskinbutton;
    	      ImageButton shopfoodbutton   = guiManager.get().shopfoodbutton;
    	      ImageButton shoparmbutton    = guiManager.get().shoparmbutton;
    	      ImageButton shopbearbutton   = guiManager.get().shopbearbutton;
    	      ImageButton shopcatbutton    = guiManager.get().shopcatbutton;
    	      ImageButton shoprabbitbutton = guiManager.get().shoprabbitbutton;
    	      ImageButton skinUnknown1     = guiManager.get().skinUnknown1;
    	      ImageButton skinUnknown2     = guiManager.get().skinUnknown2;
    	      ImageButton skinUnknown3     = guiManager.get().skinUnknown3;   	   
    	      ImageButton skinUpbutton     = guiManager.get().skinUpbutton;
    	      ImageButton skinDownbutton   = guiManager.get().skinDownbutton;
    	    
    	      ImageButton shopberrybutton  = guiManager.get().shopberrybutton;
    	      ImageButton shopcheesebutton = guiManager.get().shopcheesebutton;
    	  /*  ImageButton shopunknown1     = guiManager.get().shopunknown1;
    	      ImageButton shopunknown2     = guiManager.get().shopunknown2;
    	      ImageButton shopunknown3     = guiManager.get().shopunknown3;
    	      ImageButton shopunknown4     = guiManager.get().shopunknown4;
    	      ImageButton shopupbutton     = guiManager.get().shopupbutton;
    	      ImageButton shopdownbutton   = guiManager.get().shopdownbutton;  */
    	      
    	      ImageButton armarrowbutton   = guiManager.get().armarrowbutton;
    	      ImageButton armbullet1button = guiManager.get().armbullet1button;
    	      ImageButton armbullet2button = guiManager.get().armbullet2button;
    	  /*  ImageButton armUnknown1      = guiManager.get().armUnknown1;
    	      ImageButton armUnknown2      = guiManager.get().armUnknown2;
    	      ImageButton armUnknown3      = guiManager.get().armUnknown3;
    	      ImageButton armUpButton      = guiManager.get().armUpButton;
    	      ImageButton armDownButton    = guiManager.get().armDownButton;  */
    	      
    	      ImageButton advshootbutton   = guiManager.get().advshootbutton;
    	      ImageButton advmoneybutton   = guiManager.get().advmoneybutton;
    	      ImageButton advclosebutton   = guiManager.get().advclosebutton;
    	      
    	      ImageButton shotbutton       = guiManager.get().shotbutton;
    	      
            switch (msg.what)
            {
            	case SHOW_MAIN_BUTTON:         		
            		if (foodbutton != null)
            			foodbutton.setVisibility(View.VISIBLE);
            
                    if (shopbutton != null)
                      	shopbutton.setVisibility(View.VISIBLE);
                    
                    if (battlebutton != null)
                    	battlebutton.setVisibility(View.VISIBLE);
           
                    if (advbutton != null)
                    	advbutton.setVisibility(View.VISIBLE);
                    
                	if (shotbutton != null)
               		    shotbutton.setVisibility(View.GONE);                   
              		break;

            	case HIDE_MAIN_BUTTON:
            		if (foodbutton != null)	
            			foodbutton.setVisibility(View.GONE);
            		
                    if (shopbutton != null)
                      	shopbutton.setVisibility(View.GONE);
                    
                    if (battlebutton != null)
                    	battlebutton.setVisibility(View.GONE);
           
                    if (advbutton != null)
                    	advbutton.setVisibility(View.GONE);        	
            		break;
                                   
                case SHOW_FOOD_BUTTON:
            		if (cheesebutton != null)
            			cheesebutton.setVisibility(View.VISIBLE);
            
                    if (berrybutton != null)
                      	berrybutton.setVisibility(View.VISIBLE);
                    
                    break;

                case HIDE_FOOD_BUTTON:
                    if (cheesebutton != null)
                    	cheesebutton.setVisibility(View.GONE);
                    
                    if (berrybutton != null)
                       	berrybutton.setVisibility(View.GONE);
                    
                    break;
                    
                case SHOW_SHOP_INTERFACE:
                    if (shopclosebutton != null)
                    	shopclosebutton.setVisibility(View.VISIBLE);                     
                    if (shopskinbutton != null)
                    	shopskinbutton.setVisibility(View.VISIBLE); 
                    if (shopfoodbutton != null)
                    	shopfoodbutton.setVisibility(View.VISIBLE); 
                    if (shoparmbutton != null)
                    	shoparmbutton.setVisibility(View.VISIBLE); 
                    if (shopcatbutton != null)
                    	shopcatbutton.setVisibility(View.VISIBLE);
                    if (shopbearbutton != null)
                    	shopbearbutton.setVisibility(View.VISIBLE);
                    if (shoprabbitbutton != null)
                    	shoprabbitbutton.setVisibility(View.VISIBLE);
                    if (skinUnknown1 != null)
                    	skinUnknown1.setVisibility(View.VISIBLE);  
                    if (skinUnknown2 != null)
                    	skinUnknown2.setVisibility(View.VISIBLE);   
                    if (skinUnknown3 != null)
                    	skinUnknown3.setVisibility(View.VISIBLE); 
                    if (skinUpbutton  != null)
                    	skinUpbutton.setVisibility(View.VISIBLE);   
                    if (skinDownbutton  != null)
                    	skinDownbutton.setVisibility(View.VISIBLE);
                    break;
                    
                case HIDE_SHOP_INTERFACE:
                    if (shopclosebutton != null)
                    	shopclosebutton.setVisibility(View.GONE);                  
                    if (shopskinbutton != null)
                    	shopskinbutton.setVisibility(View.GONE); 
                    if (shopfoodbutton != null)
                    	shopfoodbutton.setVisibility(View.GONE); 
                    if (shoparmbutton != null)
                    	shoparmbutton.setVisibility(View.GONE); 
                    if (shopcatbutton != null)
                    	shopcatbutton.setVisibility(View.GONE);
                    if (shopbearbutton != null)
                    	shopbearbutton.setVisibility(View.GONE);   
                    if (shoprabbitbutton != null)
                     	shoprabbitbutton.setVisibility(View.GONE);
                    if (skinUnknown1 != null)
                    	skinUnknown1.setVisibility(View.GONE);  
                    if (skinUnknown2 != null)
                    	skinUnknown2.setVisibility(View.GONE);   
                    if (skinUnknown3 != null)
                    	skinUnknown3.setVisibility(View.GONE); 
                    if (skinUpbutton  != null)
                    	skinUpbutton.setVisibility(View.GONE);   
                    if (skinDownbutton  != null)
                    	skinDownbutton.setVisibility(View.GONE);
                    
                    break;
                    
                case SHOW_USE_CAT:               	
                    if (shopcatbutton != null){
                    	shopcatbutton.setImageResource(R.drawable.skin_cat_use);   
                    }
                    break;
                    
                case SHOW_USE_RABBIT:
                    if (shoprabbitbutton != null){
                    	shoprabbitbutton.setImageResource(R.drawable.skin_rabbit_use); 
                    }
                	break;
                	
                case SHOW_USE_BEAR:
                    if (shopbearbutton != null){
                    	shopbearbutton.setImageResource(R.drawable.skin_bear_use);
                    }
                	break;

                case SHOW_SKIN_CAT:
                    if (shopcatbutton != null){
                     	shopcatbutton.setImageResource(R.drawable.shop_skin_cat);   
                    }
                 	break;

                case SHOW_SKIN_RABBIT:
                    if (shoprabbitbutton != null){
                    	shoprabbitbutton.setImageResource(R.drawable.shop_skin_rabbit);   
                    }
                	break;
                	
                case SHOW_SKIN_BEAR:
                    if (shopbearbutton != null){
                    	shopbearbutton.setImageResource(R.drawable.shop_skin_bear);   
                    }
                	break;               

                case SHOW_USE_ARROW:
                	if (armarrowbutton != null){
                		armarrowbutton.setImageResource(R.drawable.shop_arrow_lv1_use);   
                    }                	
                	break;

                case SHOW_USE_BULLET1:
                	if (armbullet1button != null){
                		armbullet1button.setImageResource(R.drawable.shop_arm_lv2_use);   
                    }                   	
                	break;
                	
                case SHOW_USE_BULLET2:
                	if (armbullet2button != null){
                		armbullet2button.setImageResource(R.drawable.shop_arm_lv3_use);   
                    }    
                	break;

                case SHOW_ARROW:
                	if (armarrowbutton != null){
                		armarrowbutton.setImageResource(R.drawable.shop_arrow_lv1);   
                    }                	
                	break;
                	
                case SHOW_BULLET1:
                	if (armbullet1button != null){
                		armbullet1button.setImageResource(R.drawable.shop_arm_lv2);   
                    }     
                	break;

                case SHOW_BULLET2:
                	if (armbullet2button != null){
                		armbullet2button.setImageResource(R.drawable.shop_arm_lv3);   
                    }     
                	break;
                	
                case SHOW_ADV_INTERFACE:
                	 if (advshootbutton != null)
                		 advshootbutton.setVisibility(View.VISIBLE);
                	 if (advmoneybutton != null)
                		 advmoneybutton.setVisibility(View.VISIBLE);
                	 if (advclosebutton != null)
                		 advclosebutton.setVisibility(View.VISIBLE);
                	break;            
                	
                case HIDE_ADV_INTERFACE:
               	 	if (advshootbutton != null)
               		    advshootbutton.setVisibility(View.GONE);
               	 	if (advmoneybutton != null)
               		    advmoneybutton.setVisibility(View.GONE);
               	 	if (advclosebutton != null)
               		    advclosebutton.setVisibility(View.GONE);
               	 	break;
               	 	
                case BUY_BERRY:
                	if(shopberrybutton != null)
                		shopberrybutton.setImageResource(R.drawable.berry_buy_selector);
                   	break;
                   	
                case CANNOT_BUY_BERRY:
                	if(shopberrybutton != null)
                		shopberrybutton.setImageResource(R.drawable.shop_food_strawberry);
                   	break;

                case BUY_CHEESE:
                	if(shopcheesebutton != null)
                		shopcheesebutton.setImageResource(R.drawable.cheese_buy_selector);
                   	break;
                   	
                case CANNOT_BUY_CHEESE:
                	if(shopcheesebutton != null)
                		shopcheesebutton.setImageResource(R.drawable.shop_food_cheese);
                   	break;
                   	
                case SHOW_SHOOT_BUTTON:
              	 	if (shotbutton != null)
               		    shotbutton.setVisibility(View.VISIBLE);
                	break; 	
                	                	
                case DISPLAY_INFO_TOAST:
                    String text = (String) msg.obj;
                    int duration = Toast.LENGTH_LONG;
                    Toast toast =
                        Toast.makeText(context, text, duration);
                    toast.show();
                    break;
                                	
                default:
                    break;                    
            }        
        }
    }
    private MyActivityHandler mainActivityHandler;

    // Flags for our Handler:
    public static final int SHOW_MAIN_BUTTON = 0;
    public static final int HIDE_MAIN_BUTTON = 1;
    public static final int SHOW_FOOD_BUTTON = 2;
    public static final int HIDE_FOOD_BUTTON = 3;
    public static final int SHOW_ADV_INTERFACE = 4;
    public static final int HIDE_ADV_INTERFACE = 5;
    
    public static final int DISPLAY_INFO_TOAST = 6;
    
    public static final int SHOW_SHOP_INTERFACE = 7;
    public static final int HIDE_SHOP_INTERFACE = 8;
    public static final int SHOW_USE_CAT     = 9;
    public static final int SHOW_USE_RABBIT  = 10;
    public static final int SHOW_USE_BEAR    = 11;
    public static final int SHOW_SKIN_CAT    = 12;
    public static final int SHOW_SKIN_RABBIT = 13;
    public static final int SHOW_SKIN_BEAR   = 14;
   
    public static final int SHOW_USE_ARROW    = 16;
    public static final int SHOW_USE_BULLET1  = 17;
    public static final int SHOW_USE_BULLET2  = 18;

    public static final int SHOW_ARROW    = 19;
    public static final int SHOW_BULLET1  = 20;
    public static final int SHOW_BULLET2  = 21;
    
    public static final int BUY_BERRY  = 22;
    public static final int BUY_CHEESE = 23;
    
    public static final int CANNOT_BUY_BERRY = 24;
    public static final int CANNOT_BUY_CHEESE = 25;
    
    public static final int SHOW_SHOOT_BUTTON = 26;

    
    // Native methods to handle button clicks:
      public native void nativeFood();
      public native void nativeShop();
      public native void nativeShopClosed();
      public native void nativeUseCat();
      public native void nativeUseBear();
      public native void nativeUseRabbit();
      
      public native void nativeBuyBerry();
      public native void nativeBuyCheese();
      
      public native void nativeUseArrow();
      public native void nativeUseBullet1();
      public native void nativeUseBullet2();
      
      public native void nativeBattle(); 
      public native void nativeAdv(); 
      public native void nativeCheese();
      public native void nativeBerry();
      
      public native void nativeShootGameStart();
      public native void nativeMoneyGameStart();
      public native void nativeAdvClosed();
      
      public native void nativeFire();

      
    /** Initialize the GUIManager. */
    public GUIManager(Context context)
    {
        // Load our overlay view:
        // NOTE: This view will add content on top of the camera / OpenGL view
        overlayView = View.inflate(context, R.layout.interface_layout, null);

        // Create a Handler from the current thread:
        // This is the only thread that can make changes to the GUI,
        // so we require a handler for other threads to make changes
        mainActivityHandler = new MyActivityHandler(this, context);
    }


    /** Button clicks should call corresponding native functions. */
    public void initButtons()
    {
        if (overlayView == null)
            return;
                
        foodbutton = (ImageButton) overlayView.findViewById(R.id.FoodButton);
        foodbutton.getBackground().setAlpha(0);
        foodbutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	nativeFood();
            }
        });
        
        cheesebutton = (ImageButton) overlayView.findViewById(R.id.CheeseButton);
        cheesebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	nativeCheese();
            }
        });
        
        berrybutton = (ImageButton) overlayView.findViewById(R.id.BerryButton);
        berrybutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	nativeBerry();
            }
        });
      
        shopbutton = (ImageButton) overlayView.findViewById(R.id.ShopButton);
        shopbutton.getBackground().setAlpha(0);
        shopbutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	nativeShop();                   	 
            	overlayView.setBackgroundResource(R.drawable.shop_background);
            }
        });    
        
            
        // skin interface in shop
        shopcatbutton = (ImageButton) overlayView.findViewById(R.id.ShopCatButton);
        shopcatbutton.getBackground().setAlpha(0);
        shopcatbutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	nativeUseCat();
            	//shopcatbutton.setImageResource(R.drawable.skin_cat_use);
            }
        });
        
        shopbearbutton = (ImageButton) overlayView.findViewById(R.id.ShopBearButton);
        shopbearbutton.getBackground().setAlpha(0);
        shopbearbutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	nativeUseBear();
            	//shopbearbutton.setImageResource(R.drawable.skin_bear_use);
            }
        });
        
        shoprabbitbutton = (ImageButton) overlayView.findViewById(R.id.ShopRabbitButton);
        shoprabbitbutton.getBackground().setAlpha(0);
        shoprabbitbutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	nativeUseRabbit();
            }
        });
        
        skinUnknown1 = (ImageButton) overlayView.findViewById(R.id.unknownSkin1);
        skinUnknown1.getBackground().setAlpha(0);
         
        skinUnknown2 = (ImageButton) overlayView.findViewById(R.id.unknownSkin2);
        skinUnknown2.getBackground().setAlpha(0);
        
        skinUnknown3 = (ImageButton) overlayView.findViewById(R.id.unknownSkin3);
        skinUnknown3.getBackground().setAlpha(0);        
        
        skinUpbutton = (ImageButton) overlayView.findViewById(R.id.skinUpButton);
        skinUpbutton.getBackground().setAlpha(0);
    
        skinDownbutton = (ImageButton) overlayView.findViewById(R.id.skinDownButton);
        skinDownbutton.getBackground().setAlpha(0);       
        
        
        // food interface in shop
        shopberrybutton = (ImageButton) overlayView.findViewById(R.id.shopBerryButton);
        shopberrybutton.getBackground().setAlpha(0);
        shopberrybutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	nativeBuyBerry();
            }
        });
        
        shopcheesebutton = (ImageButton) overlayView.findViewById(R.id.shopCheeseButton);
        shopcheesebutton.getBackground().setAlpha(0);
        shopcheesebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	nativeBuyCheese();
            }
        });
               
        shopunknown1 = (ImageButton) overlayView.findViewById(R.id.ShopUnknown1);
        shopunknown1.getBackground().setAlpha(0);
         
        shopunknown2 = (ImageButton) overlayView.findViewById(R.id.ShopUnknown2);
        shopunknown2.getBackground().setAlpha(0);
        
        shopunknown3 = (ImageButton) overlayView.findViewById(R.id.ShopUnknown3);
        shopunknown3.getBackground().setAlpha(0);
        
        shopunknown4 = (ImageButton) overlayView.findViewById(R.id.shopUnKnown4);
        shopunknown4.getBackground().setAlpha(0);
        
        shopupbutton = (ImageButton) overlayView.findViewById(R.id.ShopUpButton);
        shopupbutton.getBackground().setAlpha(0);
    
        shopdownbutton = (ImageButton) overlayView.findViewById(R.id.ShopDownButton);
        shopdownbutton.getBackground().setAlpha(0);
  
       
        // Arm interface in shop
        armarrowbutton = (ImageButton) overlayView.findViewById(R.id.shopArrowButton);
        armarrowbutton.getBackground().setAlpha(0);
        armarrowbutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	nativeUseArrow();
            }
        });
        
        armbullet1button = (ImageButton) overlayView.findViewById(R.id.shopBullet1);
        armbullet1button.getBackground().setAlpha(0);
        armbullet1button.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	nativeUseBullet1();
            }
        });
        
        armbullet2button = (ImageButton) overlayView.findViewById(R.id.shopBullet2);
        armbullet2button.getBackground().setAlpha(0);
        armbullet2button.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	nativeUseBullet2();
            }
        });
        
        armUnknown1 = (ImageButton) overlayView.findViewById(R.id.armUnKnown1);
        armUnknown1.getBackground().setAlpha(0);
         
        armUnknown2 = (ImageButton) overlayView.findViewById(R.id.armUnKnown2);
        armUnknown2.getBackground().setAlpha(0);
        
        armUnknown3 = (ImageButton) overlayView.findViewById(R.id.armUnKnown3);
        armUnknown3.getBackground().setAlpha(0);
        
        armUpButton = (ImageButton) overlayView.findViewById(R.id.armUpButton);
        armUpButton.getBackground().setAlpha(0);
    
        armDownButton = (ImageButton) overlayView.findViewById(R.id.armDownButton);
        armDownButton.getBackground().setAlpha(0);

        shopclosebutton = (ImageButton) overlayView.findViewById(R.id.ShopClosedButton);
        shopclosebutton.getBackground().setAlpha(0);
        shopclosebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	nativeShopClosed();
            	cleanFoodGoods();
            	cleanArmGoods();
            	overlayView.setBackgroundResource(0);
            }
        });   
        
        shopskinbutton = (ImageButton) overlayView.findViewById(R.id.ShopSkinButton);
        shopskinbutton.getBackground().setAlpha(0);
        shopskinbutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	showSkinGoods();
            	cleanFoodGoods();
            	cleanArmGoods();
            }
        });    
        
        shopfoodbutton = (ImageButton) overlayView.findViewById(R.id.ShopFoodButton);
        shopfoodbutton.getBackground().setAlpha(0);
        shopfoodbutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	showFoodGoods(); 
            	cleanSkinGoods();
            	cleanArmGoods();
            }
        });    
        
        shoparmbutton = (ImageButton) overlayView.findViewById(R.id.ShopArmButton);
        shoparmbutton.getBackground().setAlpha(0);
        shoparmbutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	showArmGoods();
            	cleanSkinGoods();
            	cleanFoodGoods();
            }
        });
        
        battlebutton = (ImageButton) overlayView.findViewById(R.id.BattleButton);
        battlebutton.getBackground().setAlpha(0);
        battlebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
                nativeBattle();
            }
        });
        
        shotbutton = (ImageButton) overlayView.findViewById(R.id.ShotButton);
        shotbutton.getBackground().setAlpha(0);
        shotbutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	nativeFire();
            }
        });
        
        advbutton = (ImageButton) overlayView.findViewById(R.id.AdvButton);
        advbutton.getBackground().setAlpha(0);
        advbutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	nativeAdv();
            	overlayView.setBackgroundResource(R.drawable.game_background);
            }
        });
        
        advshootbutton = (ImageButton) overlayView.findViewById(R.id.ShootGameButton);
        advshootbutton.getBackground().setAlpha(0);
        advshootbutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	nativeShootGameStart();
            	overlayView.setBackgroundResource(0);            	
            }
        });
        
        advmoneybutton = (ImageButton) overlayView.findViewById(R.id.MoneyGameButton);
        advmoneybutton.getBackground().setAlpha(0);
        advmoneybutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	nativeMoneyGameStart();
            	overlayView.setBackgroundResource(0);            	
            }
        });
        
        advclosebutton = (ImageButton) overlayView.findViewById(R.id.AdvClosedButton);
        advclosebutton.getBackground().setAlpha(0);
        advclosebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
            	nativeAdvClosed();
            	overlayView.setBackgroundResource(0);            	
            }
        });
    }
    
    /** Clear the button listeners. */
    public void deinitButtons()
    {
        if (overlayView == null)
            return;
        
        if (foodbutton != null)
        {
           	foodbutton.setOnClickListener(null);
        	foodbutton = null;
        }
        
        if (shopbutton != null)
        {
           	shopbutton.setOnClickListener(null);
        	shopbutton = null;
        }
        
        if (cheesebutton != null)
        {
        	cheesebutton.setOnClickListener(null);
           	cheesebutton = null;
        }
        
        if (berrybutton != null)
        {
           	berrybutton.setOnClickListener(null);
           	berrybutton = null;
        }
        
        if (battlebutton != null)
        {
           	battlebutton.setOnClickListener(null);
        	battlebutton = null;
        }
        
        if (advbutton != null)
        {
           	advbutton.setOnClickListener(null);
        	advbutton = null;
        }
        
        if (shopclosebutton != null)
        {
        	shopclosebutton.setOnClickListener(null);
        	shopclosebutton = null;
        }
        
        if (shopskinbutton != null)
        {
        	shopskinbutton.setOnClickListener(null);
        	shopskinbutton = null;
        }

        if (shopfoodbutton != null)
        {
        	shopfoodbutton.setOnClickListener(null);
        	shopfoodbutton = null;
        }

        if (shoparmbutton != null)
        {
        	shoparmbutton.setOnClickListener(null);
        	shoparmbutton = null;
        }

        // skin interface
        if (shopcatbutton != null)
        {
        	shopcatbutton.setOnClickListener(null);
        	shopcatbutton = null;
        }

        if (shopbearbutton != null)
        {
        	shopbearbutton.setOnClickListener(null);
        	shopbearbutton = null;
        }
        
        
        if (shoprabbitbutton != null)
        {
        	shoprabbitbutton.setOnClickListener(null);
        	shoprabbitbutton = null;
        }
        
        if (skinUnknown1 != null)
        {
        	skinUnknown1.setOnClickListener(null);
        	skinUnknown1 = null;
        }
        
        if (skinUnknown2 != null)
        {
        	skinUnknown2.setOnClickListener(null);
        	skinUnknown2 = null;
        }
        
        if (skinUnknown3 != null)
        {
        	skinUnknown3.setOnClickListener(null);
        	skinUnknown3 = null;
        }

        if (skinUpbutton != null)
        {
        	skinUpbutton.setOnClickListener(null);
        	skinUpbutton = null;
        }
        
        if (skinDownbutton != null)
        {
        	skinDownbutton.setOnClickListener(null);
        	skinDownbutton = null;
        }

        // food interface
        if (shopberrybutton != null)
        {
        	shopberrybutton.setOnClickListener(null);
        	shopberrybutton = null;
        }  
        
        if (shopcheesebutton != null)
        {
        	shopcheesebutton.setOnClickListener(null);
        	shopcheesebutton = null;
        }           
        
        if (shopunknown1 != null)
        {
        	shopunknown1.setOnClickListener(null);
        	shopunknown1 = null;
        }      
        
        if (shopunknown2 != null)
        {
        	shopunknown2.setOnClickListener(null);
        	shopunknown2 = null;
        }
        
        if (shopunknown3 != null)
        {
        	shopunknown3.setOnClickListener(null);
        	shopunknown3 = null;
        }

        if (shopunknown4 != null)
        {
        	shopunknown4.setOnClickListener(null);
        	shopunknown4 = null;
        }
        
        if (shopupbutton != null)
        {
        	shopupbutton.setOnClickListener(null);
        	shopupbutton = null;
        }
        
        if (shopdownbutton != null)
        {
        	shopdownbutton.setOnClickListener(null);
        	shopdownbutton = null;
        }
               
        // Skin interface
        if (shopcatbutton != null)
        {
        	shopcatbutton.setOnClickListener(null);
        	shopcatbutton = null;
        }

        if (shopbearbutton != null)
        {
        	shopbearbutton.setOnClickListener(null);
        	shopbearbutton = null;
        }
        
        
        if (shoprabbitbutton != null)
        {
        	shoprabbitbutton.setOnClickListener(null);
        	shoprabbitbutton = null;
        }
        
        if (skinUnknown1 != null)
        {
        	skinUnknown1.setOnClickListener(null);
        	skinUnknown1 = null;
        }
        
        if (skinUnknown2 != null)
        {
        	skinUnknown2.setOnClickListener(null);
        	skinUnknown2 = null;
        }
        
        if (skinUnknown3 != null)
        {
        	skinUnknown3.setOnClickListener(null);
        	skinUnknown3 = null;
        }

        if (skinUpbutton != null)
        {
        	skinUpbutton.setOnClickListener(null);
        	skinUpbutton = null;
        }
        
        if (skinDownbutton != null)
        {
        	skinDownbutton.setOnClickListener(null);
        	skinDownbutton = null;
        }

        // Arm interface
        if (armarrowbutton != null)
        {
        	armarrowbutton.setOnClickListener(null);
        	armarrowbutton = null;
        }  
        
        if (armbullet1button != null)
        {
        	armbullet1button.setOnClickListener(null);
        	armbullet1button = null;
        }           
        
        if (armbullet2button != null)
        {
        	armbullet2button.setOnClickListener(null);
        	armbullet2button = null;
        }      
        
        if (armUnknown1 != null)
        {
        	armUnknown1.setOnClickListener(null);
        	armUnknown1 = null;
        }
        
        if (armUnknown2 != null)
        {
        	armUnknown2.setOnClickListener(null);
        	armUnknown2 = null;
        }

        if (armUnknown3 != null)
        {
        	armUnknown3.setOnClickListener(null);
        	armUnknown3 = null;
        }
        
        if (armUpButton != null)
        {
        	armUpButton.setOnClickListener(null);
        	armUpButton = null;
        }
        
        if (armDownButton != null)
        {
        	armDownButton.setOnClickListener(null);
        	armDownButton = null;
        }
        
        
        if (advshootbutton != null)
        {
        	advshootbutton.setOnClickListener(null);
        	advshootbutton = null;
        }
        
        if (advmoneybutton != null)
        {
        	advmoneybutton.setOnClickListener(null);
        	advmoneybutton = null;
        }
        
        if (advclosebutton != null)
        {
        	advclosebutton.setOnClickListener(null);
        	advclosebutton = null;
        }
        
        if (shotbutton != null)
        {
        	shotbutton.setOnClickListener(null);
        	shotbutton = null;
        }
        
    }

    /** Send a message to our gui thread handler. */
    public void sendThreadSafeGUIMessage(Message message)
    {
        mainActivityHandler.sendMessage(message);
    }


    /** Getter for the overlay view. */
    public View getOverlayView()
    {
        return overlayView;
    }
    
    public void showSkinGoods(){
    	if (shopcatbutton != null)
    		shopcatbutton.setVisibility(View.VISIBLE);  
    	if (shopbearbutton != null)
    		shopbearbutton.setVisibility(View.VISIBLE); 
    	if (shoprabbitbutton != null)
         	shoprabbitbutton.setVisibility(View.VISIBLE);
        if (skinUnknown1 != null)
        	skinUnknown1.setVisibility(View.VISIBLE);  
        if (skinUnknown2 != null)
        	skinUnknown2.setVisibility(View.VISIBLE);   
        if (skinUnknown3 != null)
        	skinUnknown3.setVisibility(View.VISIBLE);    
        if (skinUpbutton != null)
        	skinUpbutton.setVisibility(View.VISIBLE);   
        if (skinDownbutton != null)
        	skinDownbutton.setVisibility(View.VISIBLE);   	
    }
    
    public void cleanSkinGoods(){
        if (shopcatbutton != null)
        	shopcatbutton.setVisibility(View.GONE);
        if (shopbearbutton != null)
        	shopbearbutton.setVisibility(View.GONE);
        if (shoprabbitbutton != null)
        	shoprabbitbutton.setVisibility(View.GONE);
        if (skinUnknown1 != null)
        	skinUnknown1.setVisibility(View.GONE);  
        if (skinUnknown2 != null)
        	skinUnknown2.setVisibility(View.GONE);   
        if (skinUnknown3 != null)
        	skinUnknown3.setVisibility(View.GONE);    
        if (skinUpbutton != null)
        	skinUpbutton.setVisibility(View.GONE);   
        if (skinDownbutton != null)
        	skinDownbutton.setVisibility(View.GONE);   
    }
    
    public void showFoodGoods(){
    	if (shopberrybutton != null)
    		shopberrybutton.setVisibility(View.VISIBLE);  
    	if (shopcheesebutton != null)
    		shopcheesebutton.setVisibility(View.VISIBLE);  
        if (shopunknown1 != null)
        	shopunknown1.setVisibility(View.VISIBLE);  
        if (shopunknown2 != null)
        	shopunknown2.setVisibility(View.VISIBLE);   
        if (shopunknown3 != null)
        	shopunknown3.setVisibility(View.VISIBLE);
        if (shopunknown4 != null)
        	shopunknown4.setVisibility(View.VISIBLE);  
        if (shopupbutton != null)
        	shopupbutton.setVisibility(View.VISIBLE);   
        if (shopdownbutton != null)
        	shopdownbutton.setVisibility(View.VISIBLE);      	
    }
    
    public void cleanFoodGoods(){
    	if (shopberrybutton != null)
    		shopberrybutton.setVisibility(View.GONE);  
    	if (shopcheesebutton != null)
    		shopcheesebutton.setVisibility(View.GONE);  
        if (shopunknown1 != null)
        	shopunknown1.setVisibility(View.GONE);  
        if (shopunknown2 != null)
        	shopunknown2.setVisibility(View.GONE);   
        if (shopunknown3 != null)
        	shopunknown3.setVisibility(View.GONE);
        if (shopunknown4 != null)
        	shopunknown4.setVisibility(View.GONE);  
        if (shopupbutton != null)
        	shopupbutton.setVisibility(View.GONE);   
        if (shopdownbutton != null)
        	shopdownbutton.setVisibility(View.GONE);      	
    }
    
    public void showArmGoods(){
    	if (armarrowbutton != null)
    		armarrowbutton.setVisibility(View.VISIBLE);  
    	if (armbullet1button != null)
    		armbullet1button.setVisibility(View.VISIBLE); 
    	if (armbullet2button != null)
    		armbullet2button.setVisibility(View.VISIBLE);  
        if (armUnknown1 != null)
        	armUnknown1.setVisibility(View.VISIBLE);  
        if (armUnknown2 != null)
        	armUnknown2.setVisibility(View.VISIBLE);   
        if (armUnknown3 != null)
        	armUnknown3.setVisibility(View.VISIBLE);
        if (armUpButton != null)
        	armUpButton.setVisibility(View.VISIBLE);   
        if (armDownButton != null)
        	armDownButton.setVisibility(View.VISIBLE);      	   	
    }
    
    public void cleanArmGoods(){
    	if (armarrowbutton != null)
    		armarrowbutton.setVisibility(View.GONE);  
    	if (armbullet1button != null)
    		armbullet1button.setVisibility(View.GONE); 
    	if (armbullet2button != null)
    		armbullet2button.setVisibility(View.GONE);  
        if (armUnknown1 != null)
        	armUnknown1.setVisibility(View.GONE);  
        if (armUnknown2 != null)
        	armUnknown2.setVisibility(View.GONE);   
        if (armUnknown3 != null)
        	armUnknown3.setVisibility(View.GONE);
        if (armUpButton != null)
        	armUpButton.setVisibility(View.GONE);   
        if (armDownButton != null)
        	armDownButton.setVisibility(View.GONE);      	   	
    }
    
}
