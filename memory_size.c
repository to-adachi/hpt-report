S1-AP Initial UE msg //(408)
1ap_mme_nas_procedures.c
  s1ap_mme_handle_initial_ue_message

s1ap_mme.h
  typedef struct ue_description_s {//408
   struct enb_description_s *enb;//32

    enum s1_ue_state_s        s1_ue_state;//32*5

    enb_ue_s1ap_id_t enb_ue_s1ap_id:24;//24
    mme_ue_s1ap_id_t mme_ue_s1ap_id;//32

    sctp_stream_id_t sctp_stream_recv;//16
    sctp_stream_id_t sctp_stream_send;//16

    s11_teid_t       s11_sgw_teid;//32


    /* Timer for procedure outcome issued by MME that should be answered */
    long outcome_response_timer_id;//32

    // UE Context Release procedure guard timer
    struct s1ap_timer_t       s1ap_ue_context_rel_timer;//32*2

  } ue_description_t;

mme_app_ue_context.h
typedef struct ue_context_s {
   /* Basic identifier for ue. IMSI is encoded on maximum of 15 digits of 4 bits,
    * so usage of an unsigned integer on 64 bits is necessary.
    */
   imsi64_t         imsi;                        // set by nas_auth_param_req_t //64
 #define IMSI_UNAUTHENTICATED  (0x0)
 #define IMSI_AUTHENTICATED    (0x1)
   /* Indicator to show the IMSI authentication state */
   unsigned               imsi_auth:1;                 // set by nas_auth_resp_t  //1

   enb_s1ap_id_key_t      enb_s1ap_id_key; // key uniq among all connected eNBs //64
   enb_ue_s1ap_id_t       enb_ue_s1ap_id:24; //24
   mme_ue_s1ap_id_t       mme_ue_s1ap_id;//32
   sctp_assoc_id_t        sctp_assoc_id_key;//32

   enum s1cause           ue_context_rel_cause; //32*7


 #define SUBSCRIPTION_UNKNOWN    0x0
 #define SUBSCRIPTION_KNOWN      0x1
   unsigned               subscription_known:1;        // set by S6A UPDATE LOCATION ANSWER //1
   uint8_t                msisdn[MSISDN_LENGTH+1];     // set by S6A UPDATE LOCATION ANSWER //8*16
   uint8_t                msisdn_length;               // set by S6A UPDATE LOCATION ANSWER //8   +++++++++//578

   mm_state_t             mm_state; //32*2
   ecm_state_t            ecm_state; //32*2
   /* Globally Unique Temporary Identity */
   bool                   is_guti_set;                 // is guti has been set //8
   guti_t                 guti;                        // guti.gummei.plmn set by nas_auth_param_req_t //(24+16+8) + 32
   // read by S6A UPDATE LOCATION REQUEST
   me_identity_t          me_identity;                 // not set/read except read by display utility //8*14 + 8*16

   /* TODO: Add TAI list */

   /* Last known cell identity */
   ecgi_t                  e_utran_cgi;                 // set by nas_attach_req_t //24 + 32
   // read for S11 CREATE_SESSION_REQUEST
   /* Time when the cell identity was acquired */
   time_t                 cell_age;                    // set by nas_auth_param_req_t //64

   /* TODO: add csg_id */
   /* TODO: add csg_membership */

   network_access_mode_t  access_mode;                  // set by S6A UPDATE LOCATION ANSWER //32*4  +++++++//704

   /* TODO: add ue radio cap, ms classmarks, supported codecs */

   /* TODO: add ue network capability, ms network capability */
   /* TODO: add selected NAS algorithm */

   /* TODO: add DRX parameter */

   apn_config_profile_t   apn_profile;                  // set by S6A UPDATE LOCATION ANSWER //32+(32*3)+8+(32+8+32*5+4+16)
   ard_t                  access_restriction_data;      // set by S6A UPDATE LOCATION ANSWER //32
   subscriber_status_t    sub_status;                   // set by S6A UPDATE LOCATION ANSWER //32*3
   ambr_t                 subscribed_ambr;              // set by S6A UPDATE LOCATION ANSWER //128
   ambr_t                 used_ambr;//128

   rau_tau_timer_t        rau_tau_timer;               // set by S6A UPDATE LOCATION ANSWER //32   ++++++//772

   /* Store the radio capabilities as received in S1AP UE capability indication
    * message.
    */
   uint8_t                  *ue_radio_capabilities; //8
   int                    ue_radio_cap_length; //32

   teid_t                 mme_s11_teid;                // set by mme_app_send_s11_create_session_req //32
   teid_t                 sgw_s11_teid;                // set by S11 CREATE_SESSION_RESPONSE //32
   PAA_t                  paa;                         // set by S11 CREATE_SESSION_RESPONSE //(32*5)+8*4+8*16+8  ++++//432

   // temp
   char                   pending_pdn_connectivity_req_imsi[16];//8*16
   uint8_t                pending_pdn_connectivity_req_imsi_length;//8
   bstring                pending_pdn_connectivity_req_apn;//(32+32+8)
   bstring                pending_pdn_connectivity_req_pdn_addr;//(32+32+8)
   int                    pending_pdn_connectivity_req_pti;//32
   unsigned               pending_pdn_connectivity_req_ue_id;//32
   network_qos_t          pending_pdn_connectivity_req_qos;//32*5  ++++//504
   protocol_configuration_options_t   pending_pdn_connectivity_req_pco;//(1+4+3+8+(16+8+32+32+8)*8)
   void                  *pending_pdn_connectivity_req_proc_data;//8
   int                    pending_pdn_connectivity_req_request_type;//32
   ebi_t                  default_bearer_id;//8   ++++//216
   bearer_context_t       eps_bearers[BEARERS_PER_UE];//(32+(32*5+160)+32+(32*5+160)+32*10+8+32*3+32*3)*11   ++++//13464

   // Mobile Reachability Timer-Start when UE moves to idle state. Stop when UE moves to connected state
   struct mme_app_timer_t       mobile_reachability_timer;//32*2
   // Implicit Detach Timer-Start at the expiry of Mobile Reachability timer. Stop when UE moves to connected state
   struct mme_app_timer_t       implicit_detach_timer;//32*2
   // Initial Context Setup Procedure Guard timer
   struct mme_app_timer_t       initial_context_setup_rsp_timer;//32*2  ++++//192

 } ue_context_t;
//---------------------------------------
S1-AP UE Ctxt Release Req //(0)


//---------------------------------------------
//eNodeBが追加された時の処理
//ファイル s1ap_mme_handlers.c 1133行目
//  関数 s1ap_handle_new_association()
//    呼び出しファイル s1ap_mme.c 510
//    関数 s1ap_new_enb
//    以下メモリ負荷
typedef struct enb_description_s {//328

  enum mme_s1_enb_state_s s1_state;//32*4

  char     enb_name[150];//8*150
  uint32_t enb_id;//32
  uint8_t  default_paging_drx;//8

  uint32_t nb_ue_associated;//32 
  hash_table_ts_t  ue_coll; // 8+32+32+(64+8)+8+32+8+(32+32+8)+32+32   contains ue_description_s, key is ue_description_s.?;
  sctp_assoc_id_t  sctp_assoc_id;//32
  sctp_stream_id_t next_sctp_stream;//16
  sctp_stream_id_t instreams;//16
  sctp_stream_id_t outstreams;//16

} enb_description_t;
