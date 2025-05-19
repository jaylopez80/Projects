# app.py
import streamlit as st
import tensorflow as tf
import pandas as pd
import numpy as np
import pickle
from PIL import Image
from io import BytesIO


# 1) Load your pre-trained models & metadata encoders  
@st.cache_resource
def load_models_and_encoders():
    # assuming you've saved weights / full models
    image_only = tf.keras.models.load_model('image_only_model.keras')
    multitask   = tf.keras.models.load_model('multitask_model.keras')
    fused       = tf.keras.models.load_model('fused_model.keras')
    # load sklearn objects
    
    
    type_le = pickle.load(open('type_le.pkl','rb'))
    name_le = pickle.load(open('name_le.pkl','rb'))
    X_meta_cols = pickle.load(open('X_meta_cols.pkl','rb'))
    return image_only, multitask, fused, type_le, name_le, X_meta_cols

(image_only_model,
 multitask_model,
 fused_model,
 type_le, name_le,
 X_meta_cols) = load_models_and_encoders()

# 2) Prediction helper
def preprocess_image(img: Image.Image, size=(150,150)):
    img = img.convert('RGB').resize(size)
    arr = np.array(img)/255.0
    return np.expand_dims(arr,0)

def predict_all(img: Image.Image, set_id, rarity):
    x = preprocess_image(img)
    # Meta-only
    d = pd.DataFrame([{'set.id': set_id, 'rarity': rarity}])
    Xd = pd.get_dummies(d).reindex(columns=X_meta_cols, fill_value=0)
    # Image-only
    p_img = image_only_model.predict(x)[0]
    type_img = type_le.classes_[p_img.argmax()]
    # Multitask
    p_t, p_n = multitask_model.predict(x)
    type_mt = type_le.classes_[p_t.argmax()]
    name_mt = name_le.classes_[p_n.argmax()]
    # Fused
    Xm = Xd.values.astype('float32')
    p_ft, p_fn = fused_model.predict([x, Xm])
    type_f  = type_le.classes_[p_ft.argmax()]
    name_f  = name_le.classes_[p_fn.argmax()]
    return {
      'img_only': type_img,
      'mt_type':  type_mt,
      'mt_name':  name_mt,
      'f_type':   type_f,
      'f_name':   name_f
    }
# 3) Build the Streamlit UI
st.title(" Pokédex-TCG Card Scanner")
st.markdown("""
Upload a photo or scan of a Pokémon TCG card and see four different models  
predict its **Type** (and, where available, **Name**).
""")

# pick a sample row0 from your metadata to feed set & rarity
meta = pd.read_csv("metadata.csv")
row0 = meta.sample(1).iloc[0]  

uploaded = st.file_uploader("📤 Upload card image", type=['png','jpg','jpeg'])
set_id = st.selectbox("Set ID for metadata-only", meta['set.id'].unique(), index=0)
rarity = st.selectbox("Rarity for metadata-only", meta['rarity'].fillna('Unknown').unique(), index=0)

if uploaded:
    img = Image.open(BytesIO(uploaded.read()))
    st.image(img, caption="Your card", use_column_width=True)

    st.write("### Predictions")
    preds = predict_all(img if uploaded else Image.open("cards/images/base1-11.jpg"),
                        set_id, rarity)


    st.subheader("Image-only CNN")
    st.write(f"Type: **{preds['img_only']}**")

    st.subheader("Multi-Task CNN")
    st.write(f"Type: **{preds['mt_type']}**")  
    st.write(f"Name: **{preds['mt_name']}**")

    st.subheader("Fused (Image + Meta)")
    st.write(f"Type: **{preds['f_type']}**")  
    st.write(f"Name: **{preds['f_name']}**")
