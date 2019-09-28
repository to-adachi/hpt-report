//InitialUEmessage
asn_enc_rval_t s1ap_xer_print_s1ap_initialuemessage(
    asn_app_consume_bytes_f *cb,
    void *app_key,
    s1ap_message *message_p)
{
    S1ap_InitialUEMessageIEs_t *s1ap_InitialUEMessageIEs;
    asn_enc_rval_t er;
    s1ap_InitialUEMessageIEs = &message_p->msg.s1ap_InitialUEMessageIEs;

    cb("<S1ap-InitialUEMessageIEs-PDU>\n", 31, app_key);
    xer_encode_local(&asn_DEF_S1ap_Criticality, &message_p->criticality, cb, app_key, 1);
    xer_encode_local(&asn_DEF_S1ap_ProcedureCode, &message_p->procedureCode, cb, app_key, 1);
    cb("    <S1ap-InitialUEMessageIEs>\n", 31, app_key);
    xer_encode_local(&asn_DEF_S1ap_ENB_UE_S1AP_ID, &s1ap_InitialUEMessageIEs->eNB_UE_S1AP_ID, cb, app_key, 2);
    xer_encode_local(&asn_DEF_S1ap_NAS_PDU, &s1ap_InitialUEMessageIEs->nas_pdu, cb, app_key, 2);
    xer_encode_local(&asn_DEF_S1ap_TAI, &s1ap_InitialUEMessageIEs->tai, cb, app_key, 2);
    xer_encode_local(&asn_DEF_S1ap_EUTRAN_CGI, &s1ap_InitialUEMessageIEs->eutran_cgi, cb, app_key, 2);
    xer_encode_local(&asn_DEF_S1ap_RRC_Establishment_Cause, &s1ap_InitialUEMessageIEs->rrC_Establishment_Cause, cb, app_key, 2);
    /* Optional field */
    if (s1ap_InitialUEMessageIEs->presenceMask & S1AP_INITIALUEMESSAGEIES_S_TMSI_PRESENT)
        xer_encode_local(&asn_DEF_S1ap_S_TMSI, &s1ap_InitialUEMessageIEs->s_tmsi, cb, app_key, 2);
    /* Optional field */
    if (s1ap_InitialUEMessageIEs->presenceMask & S1AP_INITIALUEMESSAGEIES_CSG_ID_PRESENT)
        xer_encode_local(&asn_DEF_S1ap_CSG_Id, &s1ap_InitialUEMessageIEs->csG_Id, cb, app_key, 2);
    /* Optional field */
    if (s1ap_InitialUEMessageIEs->presenceMask & S1AP_INITIALUEMESSAGEIES_GUMMEI_ID_PRESENT)
        xer_encode_local(&asn_DEF_S1ap_GUMMEI, &s1ap_InitialUEMessageIEs->gummei_id, cb, app_key, 2);
    /* Optional field */
    if (s1ap_InitialUEMessageIEs->presenceMask & S1AP_INITIALUEMESSAGEIES_CELLACCESSMODE_PRESENT)
        xer_encode_local(&asn_DEF_S1ap_CellAccessMode, &s1ap_InitialUEMessageIEs->cellAccessMode, cb, app_key, 2);
    /* Optional field */
    if (s1ap_InitialUEMessageIEs->presenceMask & S1AP_INITIALUEMESSAGEIES_GW_TRANSPORTLAYERADDRESS_PRESENT)
        xer_encode_local(&asn_DEF_S1ap_TransportLayerAddress, &s1ap_InitialUEMessageIEs->gW_TransportLayerAddress, cb, app_key, 2);
    /* Optional field */
    if (s1ap_InitialUEMessageIEs->presenceMask & S1AP_INITIALUEMESSAGEIES_RELAYNODE_INDICATOR_PRESENT)
        xer_encode_local(&asn_DEF_S1ap_RelayNode_Indicator, &s1ap_InitialUEMessageIEs->relayNode_Indicator, cb, app_key, 2);
    cb("    </S1ap-InitialUEMessageIEs>\n", 32, app_key);
    cb("</S1ap-InitialUEMessageIEs-PDU>\n", 32, app_key);
    _ASN_ENCODED_OK(er);
}

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

 //---------------------------------------------------
 //UE Connection release UEContextReleaseRequestIEs



//---------------------------------------------------
//UE Connection release UEContextReleaseRequestIEs
メモリ負荷なし



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

  uint32_t nb_ue_associated;//32 //1272
  hash_table_ts_t  ue_coll; // 8+32+32+(64+8)+8+32+8+(32+32+8)+32+32  //328  contains ue_description_s, key is ue_description_s.?;
  sctp_assoc_id_t  sctp_assoc_id;//32
  sctp_stream_id_t next_sctp_stream;//16
  sctp_stream_id_t instreams;//16
  sctp_stream_id_t outstreams;//16

} enb_description_t;


//-------------------------------
//処理の流れ
//initial ue message受信
s1ap_mme_nas_procedures.c s1ap_mme_handle_initial_ue_message()
  s1ap_mme_itti_messaging.h s1ap_mme_itti_mme_app_initial_ue_message()
    intertask_interface.c itti_send_msg_to_task()//メッセージ送信
mme_app_main.c mme_app_thread() //メッセージ受信
  mme_app_bearer.c mme_app_handle_initial_ue_message()
    intertask_interface.c itti_send_msg_to_task()//メッセージ送信(id = NAS_INITIAL_UE_MESSAGE)
nas_mme_task.c nas_intertask_interface() //メッセージ受信
  nas_proc.c nas_proc_establish_ind() //ここで込み入った処理をしたのち終了（細かいところまではあまり考えていない）

//initial context setup response 受信 から modify bearer request 送信
mme_app_main.c mme_app_thread() //メッセージ受信(id = MME_APP_INITIAL_CONTEXT_SETUP_RSP)
  mme_app_bearer.c  mme_app_handle_initial_context_setup_rsp()
    intertask_interface.c itti_send_msg_to_task()//メッセージ送信(id = S11_MODIFY_BEARER_REQUEST)
s11_mme_task.c s11_mme_thread() //メッセージ受信(id = S11_MODIFY_BEARER_REQUEST)
  s11_mme_bearer_manager.c s11_mme_modify_bearer_request()
    NwGtpv2c.h nwGtpv2cProcessUlpReq() //ここで込み入った処理。（おそらくGTPトンネル系の処理にシグナリングメッセージを送信）

//modify bearer response 受信
mme_app_main.c mme_app_thread() //メッセージ受信(id = S11_MODIFY_BEARER_RESPONSE)
  mme_app_statistics.c update_mme_app_stats_s1u_bearer_add() //終わり

//ue context release request 受信 から release bearer request 送信
mme_app_main.c mme_app_thread() //メッセージ受信(id = S1AP_UE_CONTEXT_RELEASE_REQ)
  mme_app_context.c mme_app_handle_s1ap_ue_context_release_req()
    mme_app_context.c _mme_app_handle_s1ap_ue_context_release ()
      mme_app_bearer.c mme_app_send_s11_release_access_bearers_req()
        intertask_interface.c itti_send_msg_to_task() //メッセージ送信(id = S11_RELEASE_ACCESS_BEARERS_REQUEST)
s11_mme_task.c 11_mme_thread() //メッセージ受信(id = S11_RELEASE_ACCESS_BEARERS_REQUEST)
  s11_mme_bearer_manager.c  s11_mme_release_access_bearers_request()
    NwGtpv2c.c nwGtpv2cProcessUlpReq() //ここで込み入った処理。（おそらくGTPトンネル系の処理にシグナリングメッセージを送信）

//release bearer response 受信 から ue release comand 送信
mme_app_main.c mme_app_thread() //メッセージ受信(id = S11_RELEASE_ACCESS_BEARERS_RESPONSE)
  mme_app_bearer.c mme_app_handle_release_access_bearers_resp()
    mme_app_itti_messaging.h mme_app_itti_ue_context_release() // Send UE Context Release Command //この処理が終了したらAAAへ
      intertask_interface.c itti_send_msg_to_task() //メッセージ送信(id = S1AP_UE_CONTEXT_RELEASE_COMMAND)
s1ap_mme.c s1ap_mme_thread() //メッセージ受信(id = S1AP_UE_CONTEXT_RELEASE_COMMAND)
  s1ap_mme_handlers.c s1ap_handle_ue_context_release_command()
    s1ap_mme_handlers.c s1ap_mme_generate_ue_context_release_command()
      s1ap_mme_itti_messaging.c  s1ap_mme_itti_send_sctp_request()
        intertask_interface.c itti_send_msg_to_task() //メッセージ送信(id = SCTP_DATA_REQ)

//AAA
mme_app_context.c mme_ue_context_update_ue_sig_connection_state()

//release bearer complete 受信
mme_app_main.c mme_app_thread()
  mme_app_context.c mme_app_handle_s1ap_ue_context_release_complete()
  QQQ //send a DELETE_SESSION_REQUEST message to the SGW
  PPP //Move the UE to Idle state
///QQQ
mme_app_detach.c mme_app_send_delete_session_request()
  intertask_interface.c itti_send_msg_to_task() //メッセージ送信(id = S11_DELETE_SESSION_REQUEST)
s11_mme_task.c s11_mme_thread() //メッセージ受信(id = S11_DELETE_SESSION_REQUEST)
  s11_mme_session_manager.c s11_mme_delete_session_request()
    NwGtpv2c.c nwGtpv2cProcessUlpReq()
///PPP
mme_app_context.c mme_ue_context_update_ue_sig_connection_state()
